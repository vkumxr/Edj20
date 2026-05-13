wifi_config_t ap_config = {
    .ap = {
        .ssid = "Edj20_AP",
        .password = "12345678",
    },
};

wifi_config_t sta_config = {
    .sta = {
        .ssid = "Factory_WiFi",
        .password = "password123",
    },
};

esp_wifi_set_mode(WIFI_MODE_APSTA);

esp_wifi_set_config(WIFI_IF_AP, &ap_config);
esp_wifi_set_config(WIFI_IF_STA, &sta_config);

esp_wifi_start();
esp_wifi_connect();
