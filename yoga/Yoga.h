/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

// Not defined in MSVC++
#ifndef NAN
static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
#define NAN (*(const float *) __nan)
#endif

#define YGUndefined NAN

#include "YGEnums.h"
#include "YGMacros.h"

YG_EXTERN_C_BEGIN

typedef struct YGSize {
  float width;
  float height;
} YGSize;

typedef struct YGValue {
  float value;
  YGUnit unit;
} YGValue;

static const YGValue YGValueUndefined = {YGUndefined, YGUnitUndefined};
static const YGValue YGValueAuto = {YGUndefined, YGUnitAuto};

typedef struct YGConfig *YGConfigRef;
typedef struct YGNode *YGNodeRef;
typedef YGSize (WIN_STDCALL *YGMeasureFunc)(YGNodeRef node,
                                float width,
                                YGMeasureMode widthMode,
                                float height,
                                YGMeasureMode heightMode);
typedef float (WIN_STDCALL *YGBaselineFunc)(YGNodeRef node, const float width, const float height);
typedef void (WIN_STDCALL *YGPrintFunc)(YGNodeRef node);
typedef int (*YGLogger)(const YGConfigRef config,
                        const YGNodeRef node,
                        YGLogLevel level,
                        const char *format,
                        va_list args);
typedef void (*YGNodeClonedFunc)(YGNodeRef oldNode,
                                 YGNodeRef newNode,
                                 YGNodeRef parent,
                                 int childIndex);

typedef void *(*YGMalloc)(size_t size);
typedef void *(*YGCalloc)(size_t count, size_t size);
typedef void *(*YGRealloc)(void *ptr, size_t size);
typedef void (*YGFree)(void *ptr);

// YGNode
WIN_EXPORT YGNodeRef WIN_STDCALL YGNodeNew(void);
WIN_EXPORT YGNodeRef WIN_STDCALL YGNodeNewWithConfig(const YGConfigRef config);
YGNodeRef YGNodeClone(const YGNodeRef node);
WIN_EXPORT void WIN_STDCALL YGNodeFree(const YGNodeRef node);
void YGNodeFreeRecursive(const YGNodeRef node);
WIN_EXPORT void WIN_STDCALL YGNodeReset(const YGNodeRef node);
WIN_EXPORT int32_t WIN_STDCALL YGNodeGetInstanceCount(void);

WIN_EXPORT void WIN_STDCALL YGNodeInsertChild(const YGNodeRef node,
                                  const YGNodeRef child,
                                  const uint32_t index);
WIN_EXPORT void WIN_STDCALL YGNodeRemoveChild(const YGNodeRef node, const YGNodeRef child);
void YGNodeRemoveAllChildren(const YGNodeRef node);
WIN_EXPORT YGNodeRef WIN_STDCALL YGNodeGetChild(const YGNodeRef node, const uint32_t index);
YGNodeRef YGNodeGetParent(const YGNodeRef node);
WIN_EXPORT uint32_t WIN_STDCALL YGNodeGetChildCount(const YGNodeRef node);

WIN_EXPORT void WIN_STDCALL YGNodeSetIsReferenceBaseline(
    YGNodeRef node,
    bool isReferenceBaseline);

WIN_EXPORT bool WIN_STDCALL YGNodeIsReferenceBaseline(YGNodeRef node);

WIN_EXPORT void WIN_STDCALL YGNodeCalculateLayout(const YGNodeRef node,
                                      const float availableWidth,
                                      const float availableHeight,
                                      const YGDirection parentDirection);

// Mark a node as dirty. Only valid for nodes with a custom measure function
// set.
// YG knows when to mark all other nodes as dirty but because nodes with
// measure functions
// depends on information not known to YG they must perform this dirty
// marking manually.
WIN_EXPORT void WIN_STDCALL YGNodeMarkDirty(const YGNodeRef node);
WIN_EXPORT bool WIN_STDCALL YGNodeIsDirty(const YGNodeRef node);

WIN_EXPORT void WIN_STDCALL YGNodePrint(const YGNodeRef node, const YGPrintOptions options);

WIN_EXPORT bool WIN_STDCALL YGFloatIsUndefined(const float value);

bool YGNodeCanUseCachedMeasurement(const YGMeasureMode widthMode,
                                              const float width,
                                              const YGMeasureMode heightMode,
                                              const float height,
                                              const YGMeasureMode lastWidthMode,
                                              const float lastWidth,
                                              const YGMeasureMode lastHeightMode,
                                              const float lastHeight,
                                              const float lastComputedWidth,
                                              const float lastComputedHeight,
                                              const float marginRow,
                                              const float marginColumn,
                                              const YGConfigRef config);

WIN_EXPORT void WIN_STDCALL YGNodeCopyStyle(const YGNodeRef dstNode, const YGNodeRef srcNode);

#define YG_NODE_PROPERTY(type, name, paramName)                          \
  WIN_EXPORT void WIN_STDCALL YGNodeSet##name(const YGNodeRef node, type paramName); \
  WIN_EXPORT type WIN_STDCALL YGNodeGet##name(const YGNodeRef node);

#define YG_NODE_STYLE_PROPERTY(type, name, paramName)                               \
  WIN_EXPORT void WIN_STDCALL YGNodeStyleSet##name(const YGNodeRef node, const type paramName); \
  WIN_EXPORT type WIN_STDCALL YGNodeStyleGet##name(const YGNodeRef node);

#define YG_NODE_STYLE_PROPERTY_UNIT(type, name, paramName)                                    \
  WIN_EXPORT void WIN_STDCALL YGNodeStyleSet##name(const YGNodeRef node, const float paramName);          \
  WIN_EXPORT void WIN_STDCALL YGNodeStyleSet##name##Percent(const YGNodeRef node, const float paramName); \
  WIN_EXPORT type WIN_STDCALL YGNodeStyleGet##name(const YGNodeRef node);

#define YG_NODE_STYLE_PROPERTY_UNIT_AUTO(type, name, paramName) \
  YG_NODE_STYLE_PROPERTY_UNIT(type, name, paramName)            \
  WIN_EXPORT void WIN_STDCALL YGNodeStyleSet##name##Auto(const YGNodeRef node);

#define YG_NODE_STYLE_EDGE_PROPERTY(type, name, paramName)    \
  WIN_EXPORT void WIN_STDCALL YGNodeStyleSet##name(const YGNodeRef node,  \
                                       const YGEdge edge,     \
                                       const type paramName); \
  WIN_EXPORT type WIN_STDCALL YGNodeStyleGet##name(const YGNodeRef node, const YGEdge edge);

#define YG_NODE_STYLE_EDGE_PROPERTY_UNIT(type, name, paramName)         \
  WIN_EXPORT void WIN_STDCALL YGNodeStyleSet##name(const YGNodeRef node,            \
                                       const YGEdge edge,               \
                                       const float paramName);          \
  WIN_EXPORT void WIN_STDCALL YGNodeStyleSet##name##Percent(const YGNodeRef node,   \
                                                const YGEdge edge,      \
                                                const float paramName); \
  WIN_EXPORT WIN_STRUCT(type) WIN_STDCALL YGNodeStyleGet##name(const YGNodeRef node, const YGEdge edge);

#define YG_NODE_STYLE_EDGE_PROPERTY_UNIT_AUTO(type, name) \
  WIN_EXPORT void WIN_STDCALL YGNodeStyleSet##name##Auto(const YGNodeRef node, const YGEdge edge);

#define YG_NODE_LAYOUT_PROPERTY(type, name) \
  WIN_EXPORT type WIN_STDCALL YGNodeLayoutGet##name(const YGNodeRef node);

#define YG_NODE_LAYOUT_EDGE_PROPERTY(type, name) \
  WIN_EXPORT type WIN_STDCALL YGNodeLayoutGet##name(const YGNodeRef node, const YGEdge edge);

YG_NODE_PROPERTY(void *, Context, context);
YG_NODE_PROPERTY(YGMeasureFunc, MeasureFunc, measureFunc);
YG_NODE_PROPERTY(YGBaselineFunc, BaselineFunc, baselineFunc)
YG_NODE_PROPERTY(YGPrintFunc, PrintFunc, printFunc);
YG_NODE_PROPERTY(bool, HasNewLayout, hasNewLayout);
YG_NODE_PROPERTY(YGNodeType, NodeType, nodeType);

YG_NODE_STYLE_PROPERTY(YGDirection, Direction, direction);
YG_NODE_STYLE_PROPERTY(YGFlexDirection, FlexDirection, flexDirection);
YG_NODE_STYLE_PROPERTY(YGJustify, JustifyContent, justifyContent);
YG_NODE_STYLE_PROPERTY(YGAlign, AlignContent, alignContent);
YG_NODE_STYLE_PROPERTY(YGAlign, AlignItems, alignItems);
YG_NODE_STYLE_PROPERTY(YGAlign, AlignSelf, alignSelf);
YG_NODE_STYLE_PROPERTY(YGPositionType, PositionType, positionType);
YG_NODE_STYLE_PROPERTY(YGWrap, FlexWrap, flexWrap);
YG_NODE_STYLE_PROPERTY(YGOverflow, Overflow, overflow);
YG_NODE_STYLE_PROPERTY(YGDisplay, Display, display);

YG_NODE_STYLE_PROPERTY(float, Flex, flex);
YG_NODE_STYLE_PROPERTY(float, FlexGrow, flexGrow);
YG_NODE_STYLE_PROPERTY(float, FlexShrink, flexShrink);
YG_NODE_STYLE_PROPERTY_UNIT_AUTO(YGValue, FlexBasis, flexBasis);

YG_NODE_STYLE_EDGE_PROPERTY_UNIT(YGValue, Position, position);
YG_NODE_STYLE_EDGE_PROPERTY_UNIT(YGValue, Margin, margin);
YG_NODE_STYLE_EDGE_PROPERTY_UNIT_AUTO(YGValue, Margin);
YG_NODE_STYLE_EDGE_PROPERTY_UNIT(YGValue, Padding, padding);
YG_NODE_STYLE_EDGE_PROPERTY(float, Border, border);

YG_NODE_STYLE_PROPERTY_UNIT_AUTO(YGValue, Width, width);
YG_NODE_STYLE_PROPERTY_UNIT_AUTO(YGValue, Height, height);
YG_NODE_STYLE_PROPERTY_UNIT(YGValue, MinWidth, minWidth);
YG_NODE_STYLE_PROPERTY_UNIT(YGValue, MinHeight, minHeight);
YG_NODE_STYLE_PROPERTY_UNIT(YGValue, MaxWidth, maxWidth);
YG_NODE_STYLE_PROPERTY_UNIT(YGValue, MaxHeight, maxHeight);

// Yoga specific properties, not compatible with flexbox specification
// Aspect ratio control the size of the undefined dimension of a node.
// Aspect ratio is encoded as a floating point value width/height. e.g. A value of 2 leads to a node
// with a width twice the size of its height while a value of 0.5 gives the opposite effect.
//
// - On a node with a set width/height aspect ratio control the size of the unset dimension
// - On a node with a set flex basis aspect ratio controls the size of the node in the cross axis if
// unset
// - On a node with a measure function aspect ratio works as though the measure function measures
// the flex basis
// - On a node with flex grow/shrink aspect ratio controls the size of the node in the cross axis if
// unset
// - Aspect ratio takes min/max dimensions into account
YG_NODE_STYLE_PROPERTY(float, AspectRatio, aspectRatio);

YG_NODE_LAYOUT_PROPERTY(float, Left);
YG_NODE_LAYOUT_PROPERTY(float, Top);
YG_NODE_LAYOUT_PROPERTY(float, Right);
YG_NODE_LAYOUT_PROPERTY(float, Bottom);
YG_NODE_LAYOUT_PROPERTY(float, Width);
YG_NODE_LAYOUT_PROPERTY(float, Height);
YG_NODE_LAYOUT_PROPERTY(YGDirection, Direction);
YG_NODE_LAYOUT_PROPERTY(bool, HadOverflow);

// Get the computed values for these nodes after performing layout. If they were set using
// point values then the returned value will be the same as YGNodeStyleGetXXX. However if
// they were set using a percentage value then the returned value is the computed value used
// during layout.
YG_NODE_LAYOUT_EDGE_PROPERTY(float, Margin);
YG_NODE_LAYOUT_EDGE_PROPERTY(float, Border);
YG_NODE_LAYOUT_EDGE_PROPERTY(float, Padding);

WIN_EXPORT void WIN_STDCALL YGConfigSetLogger(const YGConfigRef config, YGLogger logger);
void YGLog(const YGNodeRef node, YGLogLevel level, const char *message, ...);
void YGLogWithConfig(const YGConfigRef config, YGLogLevel level, const char *format, ...);
void YGAssert(const bool condition, const char *message);
void YGAssertWithNode(const YGNodeRef node, const bool condition, const char *message);
void YGAssertWithConfig(const YGConfigRef config,
                                   const bool condition,
                                   const char *message);

// Set this to number of pixels in 1 point to round calculation results
// If you want to avoid rounding - set PointScaleFactor to 0
WIN_EXPORT void WIN_STDCALL YGConfigSetPointScaleFactor(const YGConfigRef config, const float pixelsInPoint);

// Yoga previously had an error where containers would take the maximum space possible instead of
// the minimum
// like they are supposed to. In practice this resulted in implicit behaviour similar to align-self:
// stretch;
// Because this was such a long-standing bug we must allow legacy users to switch back to this
// behaviour.
void YGConfigSetUseLegacyStretchBehaviour(const YGConfigRef config,
                                                     const bool useLegacyStretchBehaviour);

// YGConfig
WIN_EXPORT YGConfigRef WIN_STDCALL YGConfigNew(void);
WIN_EXPORT void WIN_STDCALL YGConfigFree(const YGConfigRef config);
void YGConfigCopy(const YGConfigRef dest, const YGConfigRef src);
WIN_EXPORT int32_t WIN_STDCALL YGConfigGetInstanceCount(void);

WIN_EXPORT void WIN_STDCALL YGConfigSetExperimentalFeatureEnabled(const YGConfigRef config,
                                                      const YGExperimentalFeature feature,
                                                      const bool enabled);
WIN_EXPORT bool WIN_STDCALL YGConfigIsExperimentalFeatureEnabled(const YGConfigRef config,
                                                     const YGExperimentalFeature feature);

// Using the web defaults is the prefered configuration for new projects.
// Usage of non web defaults should be considered as legacy.
WIN_EXPORT void WIN_STDCALL YGConfigSetUseWebDefaults(const YGConfigRef config, const bool enabled);
WIN_EXPORT bool WIN_STDCALL YGConfigGetUseWebDefaults(const YGConfigRef config);

void YGConfigSetNodeClonedFunc(const YGConfigRef config,
                                          const YGNodeClonedFunc callback);

// Export only for C#
WIN_EXPORT YGConfigRef WIN_STDCALL YGConfigGetDefault(void);

WIN_EXPORT void WIN_STDCALL YGConfigSetContext(const YGConfigRef config, void *context);
WIN_EXPORT void *WIN_STDCALL YGConfigGetContext(const YGConfigRef config);

WIN_EXPORT void WIN_STDCALL
YGSetMemoryFuncs(YGMalloc ygmalloc, YGCalloc yccalloc, YGRealloc ygrealloc, YGFree ygfree);

YG_EXTERN_C_END
