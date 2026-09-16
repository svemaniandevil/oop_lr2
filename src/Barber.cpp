#include "Barber.h"

#include <fstream>
#include <iostream>

#include "Client.h"
#include "Global.h"

Barber::Barber()
    : name_("Невідомий"),
    id_(0),
    specialization_("універсал"),
    price_per_cut_(kDefaultPricePerCut),
    rating_(kDefaultRating),
    experience_years_(kDefaultExperienceYears),
    served_clients_count_(0)
{
    hairstyle_catalog_.push_back("Класична стрижка");
}

Barber::Barber(const std::string& name, uint32_t id,
    const std::string& specialization, double price_per_cut,
    double rating, uint8_t experience_years)
    : name_(name),
    id_(id),
    specialization_(specialization),
    experience_years_(experience_years),
    served_clients_count_(0)
{
    if (!SetPricePerCut(price_per_cut))
        price_per_cut_ = kDefaultPricePerCut;
    if (!SetRating(rating))
        rating_ = kDefaultRating;
    hairstyle_catalog_.push_back("Класична стрижка");
}

Barber::~Barber() { }


void Barber::AddHairstyle(const std::string& style)
{
    hairstyle_catalog_.push_back(style);
}

void Barber::DisplayCatalog() const
{
    std::cout << "Перукар: " << name_ << " (ID " << id_
        << "), спеціалізація: " << specialization_
        << ", рейтинг: " << rating_ << ", стаж: " << (int)experience_years_
        << " р., обслуговано клієнтів: " << served_clients_count_
        << std::endl;
    std::cout << "  Каталог зачісок: ";
    for (const auto& style : hairstyle_catalog_)
        std::cout << "[" << style << "] ";
    std::cout << std::endl;
}

void Barber::ServeClient(Client& client)
{
    std::string style = hairstyle_catalog_.empty()
        ? "стандартна стрижка"
        : hairstyle_catalog_.front();
    std::cout << client.name_ << " отримує зачіску \"" << style
        << "\" від перукаря " << name_ << std::endl;
    if (client.PayForService(price_per_cut_)) {
        ++served_clients_count_;
        g_total_revenue += price_per_cut_;
        std::cout << "  Оплата " << price_per_cut_ << " грн прийнята."
            << std::endl;
    }
    else
        std::cout << "  Недостатньо коштів у клієнта " << client.name_ << "!"
            << std::endl;
}

void Barber::ServeClient(Client& client, const std::string& chosen_style)
{
    bool found = false;
    for (const auto& style : hairstyle_catalog_)
        if (style == chosen_style)
        {
            found = true;
            break;
        }
    double final_price =
        found ? price_per_cut_ : price_per_cut_ * kNoStyleSurcharge;
    std::cout << client.name_ << " обирає зачіску \"" << chosen_style
        << "\" у перукаря " << name_ << std::endl;
    if (client.PayForService(final_price))
    {
        ++served_clients_count_;
        g_total_revenue += final_price;
        std::cout << "  Оплата " << final_price << " грн прийнята." << std::endl;
    }
    else
        std::cout << "  Недостатньо коштів у клієнта " << client.name_ << "!"
            << std::endl;
}

double Barber::CalculateMonthlyEarnings(uint8_t days_worked) const
{
    double base_income = price_per_cut_ * served_clients_count_;
    double experience_bonus = experience_years_ * 50.0;
    return base_income + experience_bonus * (days_worked / 30.0);
}

Barber Barber::GetBetterBarber(const Barber& other) const
{
    double this_score = rating_ * 10 + experience_years_;
    double other_score = other.rating_ * 10 + other.experience_years_;
    return (this_score >= other_score) ? *this : other;
}

void Barber::SaveToFile(const std::string& filename) const
{
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename
            << std::endl;
        return;
    }
    out << name_ << '\n'
        << id_ << '\n'
        << specialization_ << '\n'
        << price_per_cut_ << '\n'
        << rating_ << '\n'
        << (int)experience_years_ << '\n'
        << served_clients_count_ << '\n'
        << hairstyle_catalog_.size() << '\n';
    for (const auto& style : hairstyle_catalog_)
        out << style << '\n';
}

void Barber::LoadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Не вдалося відкрити файл для читання: " << filename
            << std::endl;
        return;
    }
    size_t catalog_size = 0;
    std::getline(in, name_);
    in >> id_;
    in.ignore();
    std::getline(in, specialization_);
    int experience_years = 0;
    in >> price_per_cut_ >> rating_ >> experience_years >>
        served_clients_count_ >> catalog_size;
    experience_years_ = (uint8_t)experience_years;
    in.ignore();
    hairstyle_catalog_.clear();
    for (size_t i = 0; i < catalog_size; ++i)
    {
        std::string style;
        std::getline(in, style);
        hairstyle_catalog_.push_back(style);
    }
}

int* Barber::GenerateRandomExperienceHistory(int* out_size) const {
    return GenerateSortedRandomArray(experience_years_ * 3 + 1, out_size);
}

double Barber::GetPricePerCut() const { return price_per_cut_; }
double Barber::GetRating() const { return rating_; }
uint8_t Barber::GetExperienceYears() const { return experience_years_; }
uint16_t Barber::GetServedClientsCount() const { return served_clients_count_; }

bool Barber::SetPricePerCut(double price_per_cut)
{
    if (price_per_cut > 0.0)
    {
        price_per_cut_ = price_per_cut;
        return true;
    }
    return false;
}

bool Barber::SetRating(double rating)
{
    if (rating >= 1.0 && rating <= 5.0)
    {
        rating_ = rating;
        return true;
    }
    return false;
}
