#include "../includes/iot_devices.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <iomanip>
#include <limits>
#include <thread>
#include <chrono>
#include <stdexcept>

using std::cout;
using std::cin;
using std::string;
using std::optional;
using std::move;
using std::left;
using std::setw;
using std::numeric_limits;
using std::streamsize;
using std::exception;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~METADATA~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool MetaData::is_valid_error_count(int number_of_errors) noexcept {
    return number_of_errors >= 0 && number_of_errors <= 10000;
}

bool MetaData::is_valid_ipv4(const string& ipv4) noexcept {
    if (ipv4.empty()) return false;
    struct sockaddr_in sa;
    return inet_pton(AF_INET, ipv4.c_str(), &(sa.sin_addr)) == 1;
}

bool MetaData::is_valid_ipv6(const string& ipv6) noexcept {
    if (ipv6.empty()) return false;
    struct in6_addr sa6;
    return inet_pton(AF_INET6, ipv6.c_str(), &sa6) == 1;
}

MetaData::MetaData(string firmware_version, int error_count, bool is_online, optional<string> network_alias, optional<string> ipv4_address, optional<string> ipv6_address)
    : firmware_version_(move(firmware_version)), error_count_(error_count), is_online_(is_online), network_alias_(move(network_alias)), ipv4_address_(move(ipv4_address)), ipv6_address_(move(ipv6_address)) {}

void MetaData::meta_info() const noexcept {
    cout << "firmware version: " << firmware_version_ << "\n"
         << "Error count: " << error_count_ << "\n"
         << "Online: " << (is_online_ ? "yes" : "no") << "\n"
         << "Network alias: " << network_alias_.value_or("NO INFO") << "\n"
         << "IPv4: " << ipv4_address_.value_or("NO IPv4") << "\n"
         << "IPv6: " << ipv6_address_.value_or("NO IPv6") << "\n";
}

const string& MetaData::get_firmware_version() const noexcept { return firmware_version_; }
int MetaData::get_error_count() const noexcept { return error_count_; }
bool MetaData::get_is_online() const noexcept { return is_online_; }
const optional<string>& MetaData::get_network_alias() const noexcept { return network_alias_; }
const optional<string>& MetaData::get_ipv4_address() const noexcept { return ipv4_address_; }
const optional<string>& MetaData::get_ipv6_address() const noexcept { return ipv6_address_; }

MetaData& MetaData::set_firmware_version(string new_firmware_version) noexcept {
    auto temp = move(new_firmware_version);
    firmware_version_.swap(temp);
    return *this;
}
MetaData& MetaData::reset_error_count() noexcept {
    error_count_  = 0;
    return *this;
}
MetaData& MetaData::set_error_count(int new_error_count) {
    if (!is_valid_error_count(new_error_count)) throw std::invalid_argument("ERROR: Error count is out of range!");
    error_count_ = new_error_count;
    return *this;
}
MetaData& MetaData::set_online_status(bool new_online_status) noexcept {
    is_online_ = new_online_status;
    return *this;
}
MetaData& MetaData::set_network_alias(optional<string> new_network_alias) noexcept {
    auto temp = move(new_network_alias);
    network_alias_.swap(temp);
    return *this;
}
MetaData& MetaData::set_ipv4_address(optional<string> new_ipv4) {
    if (new_ipv4.has_value() && !is_valid_ipv4(*new_ipv4)) throw std::invalid_argument("ERROR: Ipv4 is not valid!");
    auto temp = move(new_ipv4);
    ipv4_address_.swap(temp);
    return *this;
}
MetaData& MetaData::set_ipv6_address(optional<string> new_ipv6) {
    if (new_ipv6.has_value() && !is_valid_ipv6(*new_ipv6)) throw std::invalid_argument("ERROR: Ipv6 is not valid!");
    auto temp = move(new_ipv6);
    ipv6_address_.swap(temp);
    return *this;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~NAMEPLATE~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool NameplateData::is_valid_manufacture_year(int manufacture_year) noexcept {
    return manufacture_year >= 1900 && manufacture_year <= 2100;
}

NameplateData::NameplateData(string manufacturer, int manufacture_year, string serial_number, optional<string> country_of_origin, optional<string> model)
    : manufacturer_(move(manufacturer)), manufacture_year_(manufacture_year), serial_number_(move(serial_number)), country_of_origin_(move(country_of_origin)), model_(move(model)) {}

void NameplateData::nameplate_info() const noexcept {
    cout << "Manufacturer: " << manufacturer_ << "; \n"
         << "Model: " << model_.value_or("Unknown;") << "\n"
         << "Year: " << manufacture_year_ << "; \n"
         << "Origin: " << country_of_origin_.value_or("N/A;") << "\n";
}

const string& NameplateData::get_manufacturer() const noexcept { return manufacturer_; }
int NameplateData::get_manufacture_year() const noexcept { return manufacture_year_; }
const string& NameplateData::get_serial_number() const noexcept { return serial_number_; }
const optional<string>& NameplateData::get_country_of_origin() const noexcept { return country_of_origin_; }
const optional<string>& NameplateData::get_model() const noexcept { return model_; }

NameplateData& NameplateData::set_manufacturer(string new_manufacturer) noexcept {
    auto temp = move(new_manufacturer);
    manufacturer_.swap(temp);
    return *this;
}
NameplateData& NameplateData::set_manufacture_year(int new_man_year) {
    if (!is_valid_manufacture_year(new_man_year)) throw std::invalid_argument("ERROR: Year is out of range!");
    manufacture_year_ = new_man_year;
    return *this;
}
NameplateData& NameplateData::set_serial_number(string new_serial_number) noexcept {
    auto temp = move(new_serial_number);
    serial_number_.swap(temp);
    return *this;
}
NameplateData& NameplateData::set_country_of_origin(optional<string> new_country_origin) {
    auto temp = move(new_country_origin);
    country_of_origin_.swap(temp);
    return *this;
}
NameplateData& NameplateData::set_model(optional<string> new_model) noexcept {
    auto temp = move(new_model);
    model_.swap(temp);
    return *this;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~DEVICE~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

NameplateData& Device::get_nameplate() noexcept { return nameplate_; }
MetaData& Device::get_meta() noexcept { return meta_; }

void Device::display_info() const noexcept {
    cout << "\n========================================\n";
    cout << "          DEVICE SPECIFICATIONS         \n";
    cout << "========================================\n";
    cout << "--- NAMEPLATE DATA ---\n";
    cout << "| " << left << setw(20) << "Manufacturer:"    << nameplate_.get_manufacturer() << "\n";
    cout << "| " << left << setw(20) << "Model:"           << nameplate_.get_model().value_or("N/A") << "\n";
    cout << "| " << left << setw(20) << "Year:"            << nameplate_.get_manufacture_year() << "\n";
    cout << "| " << left << setw(20) << "Serial Number:"   << nameplate_.get_serial_number() << "\n";
    cout << "| " << left << setw(20) << "Origin:"          << nameplate_.get_country_of_origin().value_or("N/A") << "\n";
    
    cout << "\n--- NETWORK & STATUS ---\n";
    cout << "| " << left << setw(20) << "Firmware:"        << meta_.get_firmware_version() << "\n";
    cout << "| " << left << setw(20) << "Status:"          << (meta_.get_is_online() ? "ONLINE" : "OFFLINE") << "\n";
    cout << "| " << left << setw(20) << "Errors Count:"    << meta_.get_error_count() << "\n";
    cout << "| " << left << setw(20) << "Network Alias:"   << meta_.get_network_alias().value_or("Unassigned") << "\n";
    cout << "| " << left << setw(20) << "IPv4 Address:"    << meta_.get_ipv4_address().value_or("No IPv4") << "\n";
    cout << "| " << left << setw(20) << "IPv6 Address:"    << meta_.get_ipv6_address().value_or("No IPv6") << "\n";
    cout << "========================================\n\n";
}

void Device::interactive_setup() {
    int choice;
    string input_str;
    int input_int;

    while (true) {
        cout << "\n>>> INTERACTIVE DEVICE SETUP <<<\n";
        cout << "[1] Set Manufacturer\n[2] Set Manufacture Year\n[3] Set Firmware Version\n";
        cout << "[4] Set IPv4 Address\n[5] Toggle Online Status\n[6] Display Device Info\n[0] Exit Setup\nSelect an option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[!] Invalid input. Numbers only!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1: cout << "Enter Manufacturer: "; getline(cin, input_str); nameplate_.set_manufacturer(input_str); cout << "[+] Manufacturer updated.\n"; break;
                case 2: cout << "Enter Year (1900-2100): "; cin >> input_int; nameplate_.set_manufacture_year(input_int); cout << "[+] Year updated.\n"; break;
                case 3: cout << "Enter Firmware Version: "; getline(cin, input_str); meta_.set_firmware_version(input_str); cout << "[+] Firmware updated.\n"; break;
                case 4: cout << "Enter IPv4 Address: "; getline(cin, input_str); meta_.set_ipv4_address(input_str); cout << "[+] Network configuration saved.\n"; break;
                case 5: meta_.set_online_status(!meta_.get_is_online()); cout << "[+] Device is now " << (meta_.get_is_online() ? "ONLINE" : "OFFLINE") << ".\n"; break;
                case 6: display_info(); break;
                case 0: cout << "Saving configuration and exiting setup...\n"; return;
                default: cout << "[!] Unknown option. Try again.\n";
            }
        } catch (const exception& e) {
            cout << "[-] ERROR: " << e.what() << "\n";
        }
    }
}

void Device::connect() { cout << BLUE << "[Device]" << RESET << " connected throught usual portal...\n"; }
void Device::connect(const string& specific_ip) { cout << BLUE << "[Device]" << RESET << "  connected to " << specific_ip << "...\n"; }
void Device::turn_on() { cout << BLUE << "[Device]" << RESET << "  power is on.\n"; }
void Device::turn_off() { cout << BLUE << "[Device]" << RESET << "  power is off.\n"; }
void Device::diagnostic() const { cout << BLUE << "[Device]" << RESET << "  Base diagnostic:\n| Battery level: " << battery_level_ << "%\n"; }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~DEVICESS~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void SecurityCamera::turn_on() {
    cout << RED << "[SecurityCamera]" << RESET << "  Calibrating.." << BLINK << ".\n" << RESET;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << RED << "[SecurityCamera]" << RESET << "  Connected\n";
}
void SecurityCamera::start_stream() { cout << RED << "[SecurityCamera]" << RESET << "  Translation will be avaiable soon!\n"; }
void SecurityCamera::take_photo() { cout << RED << "[SecurityCamera]" << RESET << "  *SNAP* Photo taken!\n"; }
void SecurityCamera::toggle_night_vision() {
    night_vision_active_ = !night_vision_active_;
    cout << RED << "[SecurityCamera]" << RESET << "  Night vision: " << (night_vision_active_ ? "ON" : "OFF") << "\n";
}

void TV::turn_on() { cout << RED << "[TV]" << RESET << " , loading WebOS.." << BLINK << ".\n" << RESET; }
void TV::diagnostic() const { cout << RED << "[TV]" << RESET<< "  Base diagnostic:\n| Battery level: " << battery_level_ << "%\n" << "| Channel: " << current_channel_ << "\n"; }

void Phone::make_call(const string& number) { cout << RED << "[Phone]" << RESET << "  calling " << number << ".." << BLINK << ".\n" << RESET; }

void CellPhone::turn_on() {
    cout << RED << "[CellPhone]" << RESET << "  Searching for network.." << BLINK << ".\n" << RESET;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    cout << RED << "[CellPhone]" << RESET << "  Connected\n";
}
void CellPhone::make_call(const string& number) {
    if (battery_level_ < 5) { cout << RED << "[CellPhone]" << RESET << "  Battery level is low!\n"; return; }
    cout << RED << "[CellPhone]"<< RESET <<"  Using SIM to make a call " << number << "...\n";
    battery_level_ -= 2;
}

void SmartDoorLock::turn_on() { cout << RED << "[SmartLock]" << RESET << "  Lock is activated, waiting for a key\n"; }
void SmartDoorLock::unlock(const string& input_hash) const {
    if (input_hash == rfid_key_hash_) cout << RED << "[SmartLock]" << RESET << "  Door is unlocked\n";
    else cout << RED << "[SmartLock]" << RESET << "  ALERT! bad hash\n";
}
