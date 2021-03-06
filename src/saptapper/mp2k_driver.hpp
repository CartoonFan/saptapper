// Saptapper: Automated GSF ripper for MusicPlayer2000.

#ifndef SAPTAPPER_MP2K_DRIVER_HPP_
#define SAPTAPPER_MP2K_DRIVER_HPP_

#include <string>
#include <string_view>
#include "mp2k_driver_param.hpp"
#include "types.hpp"

namespace saptapper {

class Mp2kDriver {
 public:
  Mp2kDriver() = delete;

  static constexpr int kNoSong = -1;

  static constexpr agbsize_t gsf_driver_size() noexcept {
    return sizeof(gsf_driver_block);
  }

  static constexpr agbptr_t minigsf_address(agbptr_t gsf_driver_addr) noexcept {
    return (gsf_driver_addr != agbnullptr)
               ? (gsf_driver_addr + kSongNumberOffset)
               : agbnullptr;
  }

  static std::string name() { return "MusicPlayer2000"; }

  static Mp2kDriverParam Inspect(std::string_view rom);

  static void InstallGsfDriver(std::string& rom, agbptr_t address,
                               const Mp2kDriverParam& param);

  static int FindIdenticalSong(std::string_view rom, agbptr_t song_table,
                               int song);

 private:
  static constexpr agbsize_t kInitFnOffset = 0xd8;
  static constexpr agbsize_t kSelectSongFnOffset = 0xdc;
  static constexpr agbsize_t kMainFnOffset = 0xe0;
  static constexpr agbsize_t kVSyncFnOffset = 0xe4;
  static constexpr agbsize_t kSongNumberOffset = 0xe8;

  static constexpr unsigned char gsf_driver_block[244] = {
      0x01, 0x10, 0x8F, 0xE2, 0x11, 0xFF, 0x2F, 0xE1, 0x02, 0xA0, 0x01, 0x68,
      0x04, 0x30, 0x0A, 0x0E, 0xFB, 0xD1, 0x1F, 0xE0, 0x53, 0x61, 0x70, 0x70,
      0x79, 0x20, 0x44, 0x72, 0x69, 0x76, 0x65, 0x72, 0x20, 0x52, 0x69, 0x70,
      0x70, 0x65, 0x72, 0x20, 0x62, 0x79, 0x20, 0x43, 0x61, 0x69, 0x74, 0x53,
      0x69, 0x74, 0x68, 0x32, 0x5C, 0x5A, 0x6F, 0x6F, 0x70, 0x64, 0x2C, 0x20,
      0x28, 0x63, 0x29, 0x20, 0x32, 0x30, 0x30, 0x34, 0x2C, 0x20, 0x32, 0x30,
      0x31, 0x34, 0x20, 0x6C, 0x6F, 0x76, 0x65, 0x65, 0x6D, 0x75, 0x00, 0x00,
      0x00, 0xB5, 0x20, 0x4B, 0x00, 0xF0, 0x48, 0xF8, 0x1B, 0x48, 0x09, 0xA1,
      0x01, 0x60, 0x1B, 0x48, 0x08, 0x21, 0x41, 0x60, 0x01, 0x21, 0x1A, 0x48,
      0x01, 0x60, 0x81, 0x60, 0x1D, 0x48, 0x1A, 0x4B, 0x00, 0xF0, 0x3A, 0xF8,
      0x19, 0x4B, 0x00, 0xF0, 0x37, 0xF8, 0x05, 0xDF, 0xFA, 0xE7, 0x00, 0x00,
      0x48, 0x30, 0x9F, 0xE5, 0x00, 0x10, 0x93, 0xE5, 0x21, 0x08, 0x01, 0xE0,
      0x0F, 0x40, 0x2D, 0xE9, 0x25, 0x10, 0x8F, 0xE2, 0x01, 0x20, 0x10, 0xE2,
      0x00, 0x00, 0x00, 0x1A, 0x01, 0x00, 0x00, 0xEA, 0x0F, 0xE0, 0xA0, 0xE1,
      0x11, 0xFF, 0x2F, 0xE1, 0x0F, 0x40, 0xBD, 0xE8, 0xB2, 0x00, 0xC3, 0xE1,
      0x10, 0x30, 0x9F, 0xE5, 0x04, 0x00, 0x03, 0xE5, 0x1E, 0xFF, 0x2F, 0xE1,
      0x00, 0xB5, 0x08, 0x4B, 0x00, 0xF0, 0x12, 0xF8, 0x01, 0xBC, 0x00, 0x47,
      0xFC, 0x7F, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x04,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x00, 0xD0,
      0x18, 0x47, 0x70, 0x47};

  static agbptr_t FindInitFn(std::string_view rom, agbptr_t main_fn);
  static agbptr_t FindMainFn(std::string_view rom, agbptr_t select_song_fn);
  static agbptr_t FindVSyncFn(std::string_view rom, agbptr_t init_fn);
  static agbptr_t FindSelectSongFn(std::string_view rom);
  static agbptr_t FindSongTable(std::string_view rom, agbptr_t select_song_fn);
  static int ReadSongCount(std::string_view rom, agbptr_t song_table);
};

}  // namespace saptapper

#endif
