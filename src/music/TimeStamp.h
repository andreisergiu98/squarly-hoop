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
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//    
////////////////////////////////////////////////////////////  

#ifndef TIMESTAMP
#define TIMESTAMP

class TimeStamp {
public:
    TimeStamp();

    TimeStamp(int, int, int);

    TimeStamp(int, int, int, float);

    TimeStamp(int, int, int, char *);

    ~TimeStamp();

    void setTime(int, int, int);

    void setSeconds(int);

    void setMinutes(int);

    void setMilliseconds(int);

    void setFrequency(float);

    int getSeconds();

    int getMinutes();

    int getMilliseconds();

    float getFrequency();

    char *getMetaData();

    void setTimeWithMetaData(int, int, int, char *);

    void setTimeWithFrequency(int, int, int, float);

private:
    int minutes;
    int seconds;
    int milliseconds;
    char *metaData;
    float beatFrequency;
};

#endif
