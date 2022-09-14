#include "bn.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vlcpp/vlc.hpp>

using namespace std::chrono_literals;

bn::bn() {
  auto file_bat_stat = std::ifstream(is_charging_path);
  file_bat_stat >> bat_status;
}

bn::bn(int sleep) : sleep_time{sleep} {
  auto file_bat_stat = std::ifstream(is_charging_path);
  file_bat_stat >> bat_status;
}


void bn::show_msg() {
  auto p_result = popen(msg.c_str(), "r");
  int ch{};
  if (!p_result) {
    std::cerr << "popen failed\n";
    exit(EXIT_FAILURE);
  }
  while ((ch = fgetc(p_result)) != EOF)
    putchar(ch);

  pclose(p_result);
}

void bn::play_sound() {
  auto instance = VLC::Instance(0, nullptr);
  auto media =
      VLC::Media(instance, "../resources/ringtone.mp3", VLC::Media::FromPath);
  auto player = VLC::MediaPlayer(media);
  player.play();
  std::this_thread::sleep_for(std::chrono::seconds(10));
  player.stop();
}

void bn::start() {
  int count{};

  while (1) {
    auto file_bat_energy = std::ifstream(energy_now_path);
    file_bat_energy >> energy_now;
    auto file_bat_stat = std::ifstream(is_charging_path);
    file_bat_stat >> bat_status;

    // 23%
    if (energy_now <= 8397300 && bat_status == "Discharging") {
      std::cout << "plug the power \n";
      auto t1 = std::jthread(&bn::show_msg, this);
      auto t2 = std::jthread(&bn::play_sound, this);
      count++;
    }

    // std::cout << "battery status " << bat_status << " energy now " <<
    // energy_now
    //           << "count number " << count << std::endl;

    sleep_time += count;
    std::this_thread::sleep_for(std::chrono::minutes(sleep_time));
  }
}
