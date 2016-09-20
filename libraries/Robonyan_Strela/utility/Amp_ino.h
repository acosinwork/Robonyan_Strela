#ifndef AMP_INO
#define AMP_INO

class TimeOut
{
  public:
    bool timeout(unsigned long time);
    
  private:
    unsigned long _time = 0;
};


#endif