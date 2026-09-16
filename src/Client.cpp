#include "Client.h"

#include <fstream>
#include <iostream>

#include "Barber.h"
#include "Global.h"

Client::Client()
    : name_("Гість"),
    id_(0),
    phone_("невідомо"),
    balance_(0.0),
    age_(18),
    visit_count_(0),
    is_vip_(false),
    assigned_barber_(nullptr)
{
}

Client::Client(const std::string& name, uint32_t id, const std::string& phone,
    double balance, uint8_t age, bool is_vip)
    : name_(name),
    id_(id),
    phone_(phone),
    balance_(balance),
    age_(age),
    visit_count_(0),
    is_vip_(is_vip),
    assigned_barber_(nullptr)
{
}

Client::~Client()
{
    assigned_barber_ = nullptr;
}

void Client::BookAppointment(Barber& barber)
{
    assigned_barber_ = &barber;
    ++g_total_appointments;
    std::cout << name_ << " записався(-лась) до перукаря " << barber.name_
        << std::endl;
}

void Client::BookAppointment(Barber& barber,
    const std::string& preferred_time)
{
    assigned_barber_ = &barber;
    ++g_total_appointments;
    std::cout << name_ << " записався(-лась) до перукаря " << barber.name_
        << " на " << preferred_time << std::endl;
}

bool Client::PayForService(double amount)
{
    if (balance_ < amount)
        return false;
    balance_ -= amount;
    ++visit_count_;
    return true;
}

void Client::UpdateVipStatus()
{
    if (visit_count_ >= kVipVisitThreshold)
        is_vip_ = true;
}

Client Client::GetOlderClient(const Client& other) const
{
    return (age_ >= other.age_) ? *this : other;
}

void Client::DisplayInfo() const
{
    std::cout << "Клієнт: " << name_ << " (ID " << id_ << "), тел: " << phone_
        << ", вік: " << (int)age_ << ", баланс: " << balance_
        << " грн, візитів: " << visit_count_
        << ", VIP: " << (is_vip_ ? "так" : "ні");
    if (assigned_barber_ != nullptr)
        std::cout << ", перукар: " << assigned_barber_->name_;
    else
        std::cout << ", перукар: не призначено";
    std::cout << std::endl;
}

void Client::SaveToFile(const std::string& filename) const
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename
            << std::endl;
        return;
    }
    out << name_ << '\n'
        << id_ << '\n'
        << phone_ << '\n'
        << balance_ << '\n'
        << (int)age_ << '\n'
        << visit_count_ << '\n'
        << is_vip_ << '\n';
}

void Client::LoadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
    {
        std::cerr << "Не вдалося відкрити файл для читання: " << filename
            << std::endl;
        return;
    }
    std::getline(in, name_);
    in >> id_;
    in.ignore();
    std::getline(in, phone_);
    int age = 0;
    in >> balance_ >> age >> visit_count_ >> is_vip_;
    age_ = (uint8_t)age;
}

int* Client::GenerateRandomVisitHistory(int* out_size) const
{
    return GenerateSortedRandomArray(visit_count_ * 3 + 10, out_size);
}

double Client::GetBalance() const { return balance_; }
uint8_t Client::GetAge() const { return age_; }
uint16_t Client::GetVisitCount() const { return visit_count_; }
bool Client::IsVip() const { return is_vip_; }
Barber* Client::GetAssignedBarber() const { return assigned_barber_; }
