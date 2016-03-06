class Ultrasound {
  private:
    int trig_pin;
    int echo_pin;

  public:
    Ultrasound(int trig_pin, int echo_pin);
    void setup();
    int get_distance();
};
