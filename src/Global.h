#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <codecvt>
#include <string>

#define WString(str) std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str)
#define WriteBinary(stream, data, length) stream.write(reinterpret_cast<const char*>(data), length)
#define WriteBinaryPtr(stream, data, length) stream->write(reinterpret_cast<const char*>(data), length)

constexpr double kDefaultPricePerCut = 450.0; // UAH
constexpr double kDefaultRating = 4.0;
constexpr uint8_t kDefaultExperienceYears = 1;
constexpr uint16_t kVipVisitThreshold = 10;
constexpr double kNoStyleSurcharge = 1.2;
constexpr uint16_t kDefaultMaxQueueLength = 10;
constexpr int kMinRandomArraySize = 5;
constexpr int kMaxRandomArraySize = 10;

extern uint32_t g_total_appointments;
extern double g_total_revenue;

void InitRandomSeed();

int* GenerateSortedRandomArray(int max_value, int* out_size);

void PrintSeparator(const std::string& title);

#endif  // GLOBAL_H_
