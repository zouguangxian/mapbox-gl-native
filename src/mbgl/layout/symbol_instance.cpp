#include <mbgl/layout/symbol_instance.hpp>
#include <mbgl/style/layers/symbol_layer_properties.hpp>

namespace mbgl {

using namespace style;

namespace {
    Shaping nullShaping;
} // namespace

// We don't care which shaping we get because this is used for collision purposes
// and all the justifications have the same collision box.
const Shaping& ShapedTextOrientations::defaultHorizontalShaping() const {
    if (right) return right;
    if (center) return center;
    if (left) return left;
    return nullShaping;
}

Shaping& ShapedTextOrientations::forTextJustifyType(style::TextJustifyType type) {
    switch(type) {
    case style::TextJustifyType::Right: return right;
    case style::TextJustifyType::Left: return left;
    case style::TextJustifyType::Center: return center;
    default:
        assert(false);
        return right;
    }
}

SymbolInstance::SymbolInstance(Anchor& anchor_,
                               GeometryCoordinates line_,
                               const ShapedTextOrientations& shapedTextOrientations,
                               optional<PositionedIcon> shapedIcon,
                               const SymbolLayoutProperties::Evaluated& layout,
                               const float layoutTextSize,
                               const float textBoxScale_,
                               const float textPadding,
                               const SymbolPlacementType textPlacement,
                               const std::array<float, 2> textOffset_,
                               const float iconBoxScale,
                               const float iconPadding,
                               const std::array<float, 2> iconOffset_,
                               const GlyphPositions& positions,
                               const IndexedSubfeature& indexedFeature,
                               const std::size_t layoutFeatureIndex_,
                               const std::size_t dataFeatureIndex_,
                               const std::u16string& key_,
                               const float overscaling,
                               const float rotate,
                               float radialTextOffset_) :
    anchor(anchor_),
    line(line_),
    hasText(false),
    hasIcon(shapedIcon),

    // Create the collision features that will be used to check whether this symbol instance can be placed
    // As a collision approximation, we can use either the vertical or any of the horizontal versions of the feature
    textCollisionFeature(line_, anchor, shapedTextOrientations.defaultHorizontalShaping(), textBoxScale_, textPadding, textPlacement, indexedFeature, overscaling, rotate),
    iconCollisionFeature(line_, anchor, shapedIcon, iconBoxScale, iconPadding, indexedFeature, rotate),
    layoutFeatureIndex(layoutFeatureIndex_),
    dataFeatureIndex(dataFeatureIndex_),
    textOffset(textOffset_),
    iconOffset(iconOffset_),
    key(key_),
    textBoxScale(textBoxScale_),
    radialTextOffset(radialTextOffset_) {

    // Create the quads used for rendering the icon and glyphs.
    if (shapedIcon) {
        iconQuad = getIconQuad(*shapedIcon, layout, layoutTextSize, shapedTextOrientations.defaultHorizontalShaping());
    }

    if (shapedTextOrientations.right) {
        rightJustifiedGlyphQuads = getGlyphQuads(shapedTextOrientations.right, textOffset, layout, textPlacement, positions);
    }

    if (shapedTextOrientations.center) {
        centerJustifiedGlyphQuads = getGlyphQuads(shapedTextOrientations.center, textOffset, layout, textPlacement, positions);
    }

    if (shapedTextOrientations.left) {
        leftJustifiedGlyphQuads = getGlyphQuads(shapedTextOrientations.left, textOffset, layout, textPlacement, positions);
    }

    if (shapedTextOrientations.vertical) {
        verticalGlyphQuads = getGlyphQuads(shapedTextOrientations.vertical, textOffset, layout, textPlacement, positions);
    }

    // 'hasText' depends on finding at least one glyph in the shaping that's also in the GlyphPositionMap
    hasText = !rightJustifiedGlyphQuads.empty() || !centerJustifiedGlyphQuads.empty() || !leftJustifiedGlyphQuads.empty() ||!verticalGlyphQuads.empty();
    writingModes = WritingModeType::None;
    if (shapedTextOrientations.defaultHorizontalShaping()) {
        writingModes |= WritingModeType::Horizontal;
    } 
    if (shapedTextOrientations.vertical) {
        writingModes |= WritingModeType::Vertical;
    }
}

} // namespace mbgl
