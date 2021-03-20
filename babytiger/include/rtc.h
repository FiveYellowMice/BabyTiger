#pragma once
#include <Wire.h>
#include <RtcDS1307.h>

#define TIME_OFFSET_MIN -43200 // -12:00
#define TIME_OFFSET_MAX 50400 // +14:00

extern RtcDS1307<TwoWire> Rtc;
extern int32_t time_offset;

void time_init();

RtcDateTime rtc_local_time();

bool set_time_offset(int32_t new_time_offset);