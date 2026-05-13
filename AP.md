wifi_config_t ap_config = {
    .ap = {
        .ssid = "Edj20_AP",
        .password = "12345678",
        .max_connection = 4,
        .authmode = WIFI_AUTH_WPA_WPA2_PSK
    },
};

esp_wifi_set_mode(WIFI_MODE_AP);
esp_wifi_set_config(WIFI_IF_AP, &ap_config);
esp_wifi_start();
