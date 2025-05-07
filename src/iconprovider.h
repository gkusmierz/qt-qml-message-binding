/**
 * @file iconprovider.h
 * @brief Declaration of the IconProvider class.
 */
#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QQuickImageProvider>
#include <QJsonObject>
#include <QFont>
#include <QCache>

/**
 * @brief The IconProvider class provides icons as QImages based on font codes.
 *
 * This class loads icon font files and associated codepoints to render
 * vector icons as images requested by QML. Icons are cached to improve
 * performance for frequently used icons.
 */
class IconProvider : public QQuickImageProvider
{
public:
    /**
     * @brief Constructs an IconProvider.
     * @param familyPath Path to the font file.
     * @param codesPath Path to the icon codes file.
     */
    explicit IconProvider(const QString &familyPath, const QString &codesPath);
    
    /**
     * @brief Destructor to ensure proper cleanup of resources.
     */
    ~IconProvider();

    /**
     * @brief Overridden function to return an image for the given id.
     *
     * This method generates icons from the loaded font based on the requested
     * ID and size. It first checks the cache for previously generated icons
     * with the same specifications to avoid redundant rendering.
     *
     * @param id Icon identifier that matches a key in the codepoints map.
     * @param size Pointer to the size (output).
     * @param requestedSize Desired size.
     * @return The generated QImage.
     */
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    QMap<QString, QString> codepoints;  ///< Map of icon names to hex codepoints
    QFont font;                         ///< Font used for rendering icons
    QCache<QString, QImage> iconCache;  ///< Cache for rendered icons
    
    /**
     * @brief Converts a hex codepoint to a Unicode character.
     *
     * @param hexCodepoint The hex codepoint string.
     * @return The corresponding Unicode character.
     */
    QString hexCodepointToChar(const QString &hexCodepoint);
};

#endif // ICONPROVIDER_H
