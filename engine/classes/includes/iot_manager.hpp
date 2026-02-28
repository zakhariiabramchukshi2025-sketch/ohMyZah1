#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <arpa/inet.h>
#include <iomanip>
#include <limits>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <optional>



#include "../../system_requirements/includes/namespaces.hpp"



using std::optional;
using std::nullopt;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~COMPOSITION~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class MetaData {
private:
    std::string firmware_version_{"v1.0.0"};
    int error_count_{0};
    bool is_online_{false};
    std::optional<std::string> network_alias_{std::nullopt};
    std::optional<std::string> ipv4_address_{std::nullopt};
    std::optional<std::string> ipv6_address_{std::nullopt};
    
    [[nodiscard]] static bool is_valid_error_count(int number_of_errors) noexcept;
    [[nodiscard]] static bool is_valid_ipv4(const std::string& ipv4) noexcept;
    [[nodiscard]] static bool is_valid_ipv6(const std::string& ipv6) noexcept;

public:
    explicit MetaData(std::string firmware_version, int error_count, bool is_online,
                      std::optional<std::string> network_alias = std::nullopt,
                      std::optional<std::string> ipv4_address = std::nullopt,
                      std::optional<std::string> ipv6_address = std::nullopt);
    
    MetaData() = default;
    
    void meta_info() const noexcept;
    
    [[nodiscard]] const std::string& get_firmware_version() const noexcept;
    [[nodiscard]] int get_error_count() const noexcept;
    [[nodiscard]] bool get_is_online() const noexcept;
    [[nodiscard]] const std::optional<std::string>& get_network_alias() const noexcept;
    [[nodiscard]] const std::optional<std::string>& get_ipv4_address() const noexcept;
    [[nodiscard]] const std::optional<std::string>& get_ipv6_address() const noexcept;
        
    MetaData& set_firmware_version(std::string new_firmware_version) noexcept;
    MetaData& reset_error_count() noexcept;
    MetaData& set_error_count(int new_error_count);
    MetaData& set_online_status(bool new_online_status) noexcept;
    MetaData& set_network_alias(std::optional<std::string> new_network_alias) noexcept;
    MetaData& set_ipv4_address(std::optional<std::string> new_ipv4);
    MetaData& set_ipv6_address(std::optional<std::string> new_ipv6);
};

class NameplateData {
private:
    std::string manufacturer_{"Unknown"};
    int manufacture_year_{2000};
    std::string serial_number_{"000001"};
    std::optional<std::string> country_of_origin_{"USA"};
    std::optional<std::string> model_{"dv.1.0"};
    
    [[nodiscard]] static bool is_valid_manufacture_year(int manufacture_year) noexcept;

public:
    explicit NameplateData(std::string manufacturer, int manufacture_year, std::string serial_number,
                           std::optional<std::string> country_of_origin = std::nullopt,
                           std::optional<std::string> model = std::nullopt);

    NameplateData() = default;

    void nameplate_info() const noexcept;

    [[nodiscard]] const std::string& get_manufacturer() const noexcept;
    [[nodiscard]] int get_manufacture_year() const noexcept;
    [[nodiscard]] const std::string& get_serial_number() const noexcept;
    [[nodiscard]] const std::optional<std::string>& get_country_of_origin() const noexcept;
    [[nodiscard]] const std::optional<std::string>& get_model() const noexcept;
    
    NameplateData& set_manufacturer(std::string new_manufacturer) noexcept;
    NameplateData& set_manufacture_year(int new_man_year);
    NameplateData& set_serial_number(std::string new_serial_number) noexcept;
    NameplateData& set_country_of_origin(std::optional<std::string> new_country_origin);
    NameplateData& set_model(std::optional<std::string> new_model) noexcept;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~INTERFACESS~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class IRemoteControl {
public:
    virtual ~IRemoteControl() = default;
    virtual void turn_on() = 0;
    virtual void turn_off() = 0;
};

class IVideoStreamer {
public:
    virtual ~IVideoStreamer() = default;
    virtual void start_stream() = 0;
    virtual void take_photo() = 0;
};

class Device : public IRemoteControl {
private:
    NameplateData nameplate_;
    MetaData meta_;

protected:
    int battery_level_{100};

public:
    Device() = default;
    virtual ~Device() = default;
    
    NameplateData& get_nameplate() noexcept;
    MetaData& get_meta() noexcept;
    
    void display_info() const noexcept;
    void interactive_setup();
    
    void connect();
    void connect(const std::string& specific_ip);
    
    void turn_on() override;
    void turn_off() override;
    virtual void diagnostic() const;
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~CHILDREN~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class SecurityCamera : public Device, public IVideoStreamer {
private:
    bool night_vision_active_{false};
public:
    void turn_on() override;
    void start_stream() override;
    void take_photo() override;
    void toggle_night_vision();
};

class TV : public Device {
private:
    int current_channel_{1};
public:
    void turn_on() override;
    void diagnostic() const override;
};

class Phone : public Device {
protected:
    std::string os_version_{"Android 15"};
public:
    virtual void make_call(const std::string& number);
};

class CellPhone : public Phone {
private:
    bool has_sim_card_{true};
public:
    void turn_on() override;
    void make_call(const std::string& number) override;
};

class SmartDoorLock : public Device {
private:
    std::string rfid_key_hash_{"hash_of_your_key"};
public:
    void turn_on() override;
    void unlock(const std::string& input_hash) const;
};
