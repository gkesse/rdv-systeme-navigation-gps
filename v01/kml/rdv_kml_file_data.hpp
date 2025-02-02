#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>

namespace rdv::kml
{
    using LocalizableString = std::unordered_map<int8_t, std::string>;
    using LocalizableStringSubIndex = std::map<int8_t, uint32_t>;
    using LocalizableStringIndex = std::vector<LocalizableStringSubIndex>;
    using Properties = std::map<std::string, std::string>;

    using MarkGroupId = uint64_t;
    using MarkId = uint64_t;
    using TrackId = uint64_t;
    using LocalId = uint8_t;
    using CompilationId = uint64_t;

    using GroupIdCollection = std::vector<MarkGroupId>;

    using TimestampClock = std::chrono::system_clock;
    using Timestamp = std::chrono::time_point<TimestampClock>;

    MarkGroupId constexpr kInvalidMarkGroupId = std::numeric_limits<MarkGroupId>::max();
    MarkId constexpr kInvalidMarkId = std::numeric_limits<MarkId>::max();
    MarkId constexpr kDebugMarkId = kInvalidMarkId - 1;
    TrackId constexpr kInvalidTrackId = std::numeric_limits<TrackId>::max();
    CompilationId constexpr kInvalidCompilationId = std::numeric_limits<CompilationId>::max();

    enum class CompilationType : uint8_t
    {
        // Do not change the order because of binary serialization.
        Category = 0,
        Collection,
        Day,
    };

    /// @note Important! Should be synced with android/app/src/main/java/app/organicmaps/bookmarks/data/Icon.java
    enum class PredefinedColor : uint8_t
    {
        None = 0,
        Red,
        Blue,
        Purple,
        Yellow,
        Pink,
        Brown,
        Green,
        Orange,

        // Extended colors.
        DeepPurple,
        LightBlue,
        Cyan,
        Teal,
        Lime,
        DeepOrange,
        Gray,
        BlueGray,

        Count
    };

    enum class AccessRules : uint8_t
    {
        // Do not change the order because of binary serialization.
        Local = 0,
        Public,
        DirectLink,
        P2P,
        Paid,
        AuthorOnly,

        Count
    };

    /// @note Important! Should be synced with android/app/src/main/java/app/organicmaps/bookmarks/data/Icon.java
    enum class BookmarkIcon : uint16_t
    {
        None = 0,
        Hotel,
        Animals,
        Buddhism,
        Building,
        Christianity,
        Entertainment,
        Exchange,
        Food,
        Gas,
        Judaism,
        Medicine,
        Mountain,
        Museum,
        Islam,
        Park,
        Parking,
        Shop,
        Sights,
        Swim,
        Water,

        // Extended icons.
        Bar,
        Transport,
        Viewpoint,
        Sport,
        Pub,
        Art,
        Bank,
        Cafe,
        Pharmacy,
        Stadium,
        Theatre,
        Information,

        Count
    };

    struct ColorData
    { // Predefined color.
        PredefinedColor m_predefinedColor = PredefinedColor::None;
        // Color in RGBA format.
        uint32_t m_rgba = 0;
    };

    struct MultiGeometry
    {
        // using LineT = std::vector<geometry::PointWithAltitude>;
        using TimeT = std::vector<double>;

        // std::vector<LineT> m_lines;
        std::vector<TimeT> m_timestamps;
    };

    struct TrackLayer
    {
        // Line width in pixels. Valid range is [kMinLineWidth; kMaxLineWidth].
        double m_lineWidth = 5.0;
        // Layer's color.
        ColorData m_color;
    };

    struct CategoryData
    {
        // Unique id (it will not be serialized in text files).
        MarkGroupId m_id = kInvalidMarkGroupId;
        // Id unique within single kml (have to be serialized in text files).
        CompilationId m_compilationId = kInvalidCompilationId;
        // Unique ids of nested groups (it will not be serialized in text files).
        GroupIdCollection m_compilationIds;
        // Compilation's type
        CompilationType m_type = CompilationType::Category;
        // Category's name.
        LocalizableString m_name;
        // Image URL.
        std::string m_imageUrl;
        // Category's description.
        LocalizableString m_annotation;
        // Category's description.
        LocalizableString m_description;
        // Collection visibility.
        bool m_visible = true;
        // Author's name.
        std::string m_authorName;
        // Author's id.
        std::string m_authorId;
        // Last modification timestamp.
        Timestamp m_lastModified;
        // Rating.
        double m_rating = 0.0;
        // Number of reviews.
        uint32_t m_reviewsNumber = 0;
        // Access rules.
        AccessRules m_accessRules = AccessRules::Local;
        // Collection of tags.
        std::vector<std::string> m_tags;
        // Collection of geo ids for relevant toponyms.
        std::vector<std::string> m_toponyms;
        // Language codes.
        std::vector<int8_t> m_languageCodes;
        // Key-value properties.
        Properties m_properties;
    };

    struct BookmarkData
    {
        // Unique id (it will not be serialized in text files).
        MarkId m_id = kInvalidMarkId;
        // Bookmark's name.
        LocalizableString m_name;
        // Bookmark's description.
        LocalizableString m_description;
        // Bound feature's types: type indices sorted by importance, the most
        // important one goes first.
        std::vector<uint32_t> m_featureTypes;
        // Custom bookmark's name.
        LocalizableString m_customName;
        // Bookmark's color.
        ColorData m_color;
        // Bookmark's icon.
        BookmarkIcon m_icon = BookmarkIcon::None;
        // Viewport scale. 0 is a default value (no scale set).
        uint8_t m_viewportScale = 0;
        // Creation timestamp.
        Timestamp m_timestamp = {};
        // Coordinates in mercator.
        // m2::PointD m_point;
        // Bound tracks (vector contains local track ids).
        std::vector<LocalId> m_boundTracks;
        // Visibility.
        bool m_visible = true;
        // Nearest toponym.
        std::string m_nearestToponym;
        // Minimal zoom when bookmark is visible.
        int m_minZoom = 1;
        // List of compilationIds.
        std::vector<CompilationId> m_compilations;
        // Key-value properties.
        Properties m_properties;
    };

    struct TrackData
    {
        // Unique id (it will not be serialized in text files).
        TrackId m_id = kInvalidTrackId;
        // Local track id.
        LocalId m_localId = 0;
        // Track's name.
        LocalizableString m_name;
        // Track's description.
        LocalizableString m_description;
        // Layers.
        std::vector<TrackLayer> m_layers;
        // Creation timestamp.
        Timestamp m_timestamp = {};
        MultiGeometry m_geometry;
        // Visibility.
        bool m_visible = true;
        // Nearest toponyms.
        std::vector<std::string> m_nearestToponyms;
        // Key-value properties.
        Properties m_properties;
    };

    struct FileData
    {
        // Device id (it will not be serialized in text files).
        std::string m_deviceId;
        // Server id.
        std::string m_serverId;
        // Category's data.
        CategoryData m_categoryData;
        // Bookmarks collection.
        std::vector<BookmarkData> m_bookmarksData;
        // Tracks collection.
        std::vector<TrackData> m_tracksData;
        // Compilation collection.
        std::vector<CategoryData> m_compilationsData;
    };
}
