/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "YGEnums.h"

const char * WIN_STDCALL YGAlignToString(const YGAlign value){
  switch(value){
    case YGAlignAuto:
      return "auto";
    case YGAlignFlexStart:
      return "flex-start";
    case YGAlignCenter:
      return "center";
    case YGAlignFlexEnd:
      return "flex-end";
    case YGAlignStretch:
      return "stretch";
    case YGAlignBaseline:
      return "baseline";
    case YGAlignSpaceBetween:
      return "space-between";
    case YGAlignSpaceAround:
      return "space-around";
  }
  return "unknown";
}

const char *WIN_STDCALL YGDimensionToString(const YGDimension value){
  switch(value){
    case YGDimensionWidth:
      return "width";
    case YGDimensionHeight:
      return "height";
  }
  return "unknown";
}

const char *WIN_STDCALL YGDirectionToString(const YGDirection value){
  switch(value){
    case YGDirectionInherit:
      return "inherit";
    case YGDirectionLTR:
      return "ltr";
    case YGDirectionRTL:
      return "rtl";
  }
  return "unknown";
}

const char *WIN_STDCALL YGDisplayToString(const YGDisplay value){
  switch(value){
    case YGDisplayFlex:
      return "flex";
    case YGDisplayNone:
      return "none";
  }
  return "unknown";
}

const char *WIN_STDCALL YGEdgeToString(const YGEdge value){
  switch(value){
    case YGEdgeLeft:
      return "left";
    case YGEdgeTop:
      return "top";
    case YGEdgeRight:
      return "right";
    case YGEdgeBottom:
      return "bottom";
    case YGEdgeStart:
      return "start";
    case YGEdgeEnd:
      return "end";
    case YGEdgeHorizontal:
      return "horizontal";
    case YGEdgeVertical:
      return "vertical";
    case YGEdgeAll:
      return "all";
  }
  return "unknown";
}

const char *WIN_STDCALL YGExperimentalFeatureToString(const YGExperimentalFeature value){
  switch(value){
    case YGExperimentalFeatureWebFlexBasis:
      return "web-flex-basis";
  }
  return "unknown";
}

const char *WIN_STDCALL YGFlexDirectionToString(const YGFlexDirection value){
  switch(value){
    case YGFlexDirectionColumn:
      return "column";
    case YGFlexDirectionColumnReverse:
      return "column-reverse";
    case YGFlexDirectionRow:
      return "row";
    case YGFlexDirectionRowReverse:
      return "row-reverse";
  }
  return "unknown";
}

const char *WIN_STDCALL YGJustifyToString(const YGJustify value){
  switch(value){
    case YGJustifyFlexStart:
      return "flex-start";
    case YGJustifyCenter:
      return "center";
    case YGJustifyFlexEnd:
      return "flex-end";
    case YGJustifySpaceBetween:
      return "space-between";
    case YGJustifySpaceAround:
      return "space-around";
    case YGJustifySpaceEvenly:
      return "space-evenly";
  }
  return "unknown";
}

const char *WIN_STDCALL YGLogLevelToString(const YGLogLevel value){
  switch(value){
    case YGLogLevelError:
      return "error";
    case YGLogLevelWarn:
      return "warn";
    case YGLogLevelInfo:
      return "info";
    case YGLogLevelDebug:
      return "debug";
    case YGLogLevelVerbose:
      return "verbose";
    case YGLogLevelFatal:
      return "fatal";
  }
  return "unknown";
}

const char *WIN_STDCALL YGMeasureModeToString(const YGMeasureMode value){
  switch(value){
    case YGMeasureModeUndefined:
      return "undefined";
    case YGMeasureModeExactly:
      return "exactly";
    case YGMeasureModeAtMost:
      return "at-most";
  }
  return "unknown";
}

const char *WIN_STDCALL YGNodeTypeToString(const YGNodeType value){
  switch(value){
    case YGNodeTypeDefault:
      return "default";
    case YGNodeTypeText:
      return "text";
  }
  return "unknown";
}

const char *WIN_STDCALL YGOverflowToString(const YGOverflow value){
  switch(value){
    case YGOverflowVisible:
      return "visible";
    case YGOverflowHidden:
      return "hidden";
    case YGOverflowScroll:
      return "scroll";
  }
  return "unknown";
}

const char *WIN_STDCALL YGPositionTypeToString(const YGPositionType value){
  switch(value){
    case YGPositionTypeRelative:
      return "relative";
    case YGPositionTypeAbsolute:
      return "absolute";
  }
  return "unknown";
}

const char *WIN_STDCALL YGPrintOptionsToString(const YGPrintOptions value){
  switch(value){
    case YGPrintOptionsLayout:
      return "layout";
    case YGPrintOptionsStyle:
      return "style";
    case YGPrintOptionsChildren:
      return "children";
  }
  return "unknown";
}

const char *WIN_STDCALL YGUnitToString(const YGUnit value){
  switch(value){
    case YGUnitUndefined:
      return "undefined";
    case YGUnitPoint:
      return "point";
    case YGUnitPercent:
      return "percent";
    case YGUnitAuto:
      return "auto";
  }
  return "unknown";
}

const char *WIN_STDCALL YGWrapToString(const YGWrap value){
  switch(value){
    case YGWrapNoWrap:
      return "no-wrap";
    case YGWrapWrap:
      return "wrap";
    case YGWrapWrapReverse:
      return "wrap-reverse";
  }
  return "unknown";
}

