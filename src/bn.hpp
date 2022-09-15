#ifndef __bn_hpp__
#define __bn_hpp__
#include <string>

class bn {
public:
  bn(std::string const &, int = 5);
  void show_msg();
  void play_sound();
  void start();

private:
  int sleep_time{5}; // every 5 min checks if is battery charging or not
  int energy_now{};
  std::string bat_status;
  bool notify{false};
  const std::string energy_now_path{
      "/sys/class/power_supply/BAT0/subsystem/BAT0/energy_now"};
  const std::string is_charging_path{
      "/sys/class/power_supply/BAT0/subsystem/BAT0/status"};
  const std::string msg{"dunstify 'plug the power'"};
  std::string music_path;
};

#endif
