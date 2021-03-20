#pragma once

class Mode {
  public:
    virtual void tick() =0;
    virtual ~Mode() {}
};

extern Mode* current_mode;
extern Mode* next_mode;

void transition_mode(Mode* dst_mode);