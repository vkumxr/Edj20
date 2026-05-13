wifi_config_t sta_config = {
    .sta = {
        .ssid = "Wifi1",
        .password = "abcdefgh",
    },
};

esp_wifi_set_mode(WIFI_MODE_STA);
esp_wifi_set_config(WIFI_IF_STA, &sta_config);

esp_wifi_start();
esp_wifi_connect();
