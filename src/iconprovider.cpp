/**
 * @file iconprovider.cpp
 * @brief Implementation of the IconProvider class.
 */
#include "iconprovider.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QPainter>
#include <QFontMetrics>
#include <QFontDatabase>

/**
 * @brief Constructs an IconProvider, loads font and icon codes.
 *
 * This constructor initializes the font from the specified font file
 * and loads the icon codepoints from the codepoints file.
 *
 * @param familyPath Path to the font file (.otf, .ttf, etc.).
 * @param codesPath Path to the icon codes file (text file with name-codepoint pairs).
 */
IconProvider::IconProvider(const QString &familyPath, const QString &codesPath)
    : QQuickImageProvider(QQuickImageProvider::Image), iconCache(100) // Cache 100 most recently used icons
{
    // Load the icon font
    int id = QFontDatabase::addApplicationFont(familyPath);
    if (id == -1) {
        qWarning() << "Failed to load font from" << familyPath;
    } else {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(id);
        if (fontFamilies.isEmpty()) {
            qWarning() << "No font families found in" << familyPath;
        } else {
            QString fontFamily = fontFamilies.at(0);
            font = QFont(fontFamily);
            qDebug() << "Loaded font family:" << fontFamily;
        }
    }
    
    // Load the icon codepoints
    QFile file(codesPath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int count = 0;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList tokens = line.split(" ");
            if (tokens.size() >= 2) {
                QString key = tokens[0];
                QString value = tokens[1];
                codepoints.insert(key, value);
                count++;
            }
        }
        file.close();
        qDebug() << "Loaded" << count << "icon codepoints from" << codesPath;
    } else {
        qWarning() << "Cannot open icon codes file" << codesPath;
        qWarning() << file.errorString();
    }
}

/**
 * @brief Destructor clears the cache to prevent memory leaks.
 */
IconProvider::~IconProvider()
{
    iconCache.clear();
}

/**
 * @brief Returns an image for the requested icon id.
 *
 * This method generates an icon image based on the requested id and size.
 * It uses caching to improve performance for frequently requested icons.
 *
 * @param id Icon identifier.
 * @param size Pointer to the size (output).
 * @param requestedSize Desired size.
 * @return Generated QImage.
 */
QImage IconProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    // Determine the final size of the icon
    int width = 48;  // Default width
    int height = 48; // Default height

    if (requestedSize.width() > 0)
        width = requestedSize.width();

    if (requestedSize.height() > 0)
        height = requestedSize.height();

    if (size)
        *size = QSize(width, height);
    
    // Create a cache key that combines the icon ID and size
    QString cacheKey = QString("%1_%2x%3").arg(id).arg(width).arg(height);
    
    // Try to get the icon from cache
    QImage* cachedImage = iconCache.object(cacheKey);
    if (cachedImage) {
        return *cachedImage;
    }
    
    // Create a new image if not in cache
    QImage* image = new QImage(width, height, QImage::Format_RGBA8888);
    image->fill(QColor(Qt::transparent));
    
    // Set the appropriate font size for the icon
    QFont iconFont = font; // Create a copy of the font to avoid modifying the original
    iconFont.setPixelSize(width < height ? width : height);
    
    // Get the icon character
    QString iconChar = "?"; // Default fallback character
    
    QString hexCodepoint = codepoints.value(id).toUpper();
    if (!hexCodepoint.isEmpty()) {
        iconChar = hexCodepointToChar(hexCodepoint);
    }
    
    // Adjust font size to fit the icon character within the requested size
    QFontMetrics fontMetrics(iconFont);
    double widthRatio = double(width) / fontMetrics.boundingRect(iconChar).width();
    if (widthRatio < 1.0) {
        iconFont.setPixelSize(int(iconFont.pixelSize() * widthRatio));
    }
    
    // Draw the icon character. Set color to red for better visibility
    QPainter painter(image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setFont(iconFont);
    painter.setPen(QColor("#fffffe")); // Slightly off-white color for use with Colorization MultiEffect
    painter.drawText(QRect(0, 0, width, height), Qt::AlignCenter, iconChar);
    
    // Store in cache and return
    iconCache.insert(cacheKey, image);
    return *image;
}

/**
 * @brief Converts a hex codepoint to a Unicode character.
 *
 * This method safely converts a hexadecimal codepoint to a Unicode
 * character using Qt's built-in conversion functions to avoid memory leaks.
 *
 * @param hexCodepoint The hex codepoint string.
 * @return The corresponding Unicode character.
 */
QString IconProvider::hexCodepointToChar(const QString &hexCodepoint)
{
    if (hexCodepoint.isEmpty()) {
        return "?";
    }
    
    // Add byte order mark (BOM) to ensure proper UTF-16 encoding
    QByteArray hex = QByteArray::fromHex(QString("FEFF").append(hexCodepoint).toUtf8());
    
    // Use proper QString conversion to avoid memory issues
    QString result;
    if (hex.size() >= 2) { // Make sure we have at least 2 bytes for UTF-16
        result = QString::fromUtf16(
            reinterpret_cast<const char16_t*>(hex.constData()),
            hex.size() / 2
        );
    } else {
        result = "?";
    }
    
    return result;
}
