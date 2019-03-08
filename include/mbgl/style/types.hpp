#pragma once

#include <cstdint>

namespace mbgl {

namespace style {

// TODO: should be in public source.hpp header
enum class SourceType : uint8_t {
    Vector,
    Raster,
    RasterDEM,
    GeoJSON,
    Video,
    Annotations,
    Image,
    CustomVector
};

enum class VisibilityType : bool {
    Visible,
    None,
};

enum class LineCapType : uint8_t {
    Round,
    Butt,
    Square,
};

enum class LineJoinType : uint8_t {
    Miter,
    Bevel,
    Round,
    // the following two types are for internal use only
    FakeRound,
    FlipBevel
};

enum class RasterResamplingType : bool {
    Linear,
    Nearest
};

enum class HillshadeIlluminationAnchorType : bool {
    Map,
    Viewport
};

enum class TranslateAnchorType : bool {
    Map,
    Viewport
};

enum class RotateAnchorType : bool {
    Map,
    Viewport,
};

enum class CirclePitchScaleType : bool {
    Map,
    Viewport,
};

enum class SymbolPlacementType : uint8_t {
    Point,
    Line,
    LineCenter
};
    
enum class SymbolZOrderType : uint8_t {
    ViewportY,
    Source
};

enum class AlignmentType : uint8_t {
    Map,
    Viewport,
    Auto,
};

enum class TextJustifyType : uint8_t {
    Auto,
    Center,
    Left,
    Right
};

enum class SymbolAnchorType : uint8_t {
    Center,
    Left,
    Right,
    Top,
    Bottom,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

enum class TextVariableAnchorType : uint8_t {
    Center,
    Left,
    Right,
    Top,
    Bottom,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

enum class TextTransformType : uint8_t {
    None,
    Uppercase,
    Lowercase,
};

enum class IconTextFitType : uint8_t {
    None,
    Both,
    Width,
    Height
};

enum class LightAnchorType: bool {
    Map,
    Viewport
};

// Choose the justification that matches the direction of the TextAnchor
template <typename TextAnchorType>
static TextJustifyType getAnchorJustification(TextAnchorType anchor) {
    switch (anchor) {
    case TextAnchorType::Right:
    case TextAnchorType::TopRight:
    case TextAnchorType::BottomRight:
        return TextJustifyType::Right;
    case TextAnchorType::Left:
    case TextAnchorType::TopLeft:
    case TextAnchorType::BottomLeft:
        return TextJustifyType::Left;
    default:
        return TextJustifyType::Center;
    }
}

} // namespace style
} // namespace mbgl
