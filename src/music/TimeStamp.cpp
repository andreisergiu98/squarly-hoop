////////////////////////////////////////////////////////////
//
//      Copyright (c) 2015 Padraig O Connor
//
//      Permission is hereby granted, free of charge, to any person obtaining a copy
//      of this software and associated documentation files (the "Software"), to deal
//      in the Software without restriction, including without limitation the rights
//      to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//      copies of the Software, and to permit persons to whom the Software is
//      furnished to do so, subject to the following conditions:
//      
////////////////////////////////////////////////////////////     

#include "TimeStamp.h"

TimeStamp::TimeStamp() {
    minutes = 0;
    seconds = 0;
    milliseconds = 0;
    metaData = "";
}

TimeStamp::~TimeStamp() {
    delete metaData;
}

TimeStamp::TimeStamp(int m, int s, int mil) {
    minutes = m;
    seconds = s;
    milliseconds = mil;
    metaData = "";
}

TimeStamp::TimeStamp(int m, int s, int mil, float f) {
    minutes = m;
    seconds = s;
    milliseconds = mil;
    beatFrequency = f;
}

TimeStamp::TimeStamp(int m, int s, int mil, char *md) {
    minutes = m;
    seconds = s;
    milliseconds = mil;
    metaData = md;
}

void TimeStamp::setTime(int m, int s, int mil) {
    minutes = m;
    seconds = s;
    milliseconds = mil;
}

void TimeStamp::setMinutes(int m) {
    minutes = m;
}

void TimeStamp::setSeconds(int s) {
    seconds = s;
}

void TimeStamp::setMilliseconds(int mil) {
    milliseconds = mil;
}

void TimeStamp::setFrequency(float f) {
    beatFrequency = f;
}

void TimeStamp::setTimeWithMetaData(int m, int s, int mil, char *md) {
    minutes = m;
    seconds = s;
    milliseconds = mil;
    metaData = md;
}

void TimeStamp::setTimeWithFrequency(int m, int s, int mil, float f) {
    minutes = m;
    seconds = s;
    milliseconds = mil;
    beatFrequency = f;
}


int TimeStamp::getMinutes() {
    return minutes;
}

int TimeStamp::getSeconds() {
    return seconds;
}

int TimeStamp::getMilliseconds() {
    return milliseconds;
}

float TimeStamp::getFrequency() {
    return beatFrequency;
}

char *TimeStamp::getMetaData() {
    return metaData;
}
