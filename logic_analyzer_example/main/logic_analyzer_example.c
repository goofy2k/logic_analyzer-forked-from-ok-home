
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#ifdef CONFIG_ANALYZER_USE_SUMP 
#include "logic_analyzer_sump.h"
#endif
#ifdef CONFIG_ANALYZER_USE_WS
#include "logic_analyzer_ws_server.h"
#endif
#ifdef CONFIG_ANALYZER_USE_CLI
#include "logic_analyzer_cli.h"
#endif

void app_main(void)
{
    extern void test_sample_init();
    printf("BREADCRUMB 1\n");
    // extern void test_air();
    test_sample_init();
    // test_air();
    vTaskDelay(5);
    printf("BREADCRUMB 1a\n");
#ifdef CONFIG_ANALYZER_USE_SUMP 
    printf("BREADCRUMB 1b\n");
#ifdef CONFIG_IDF_TARGET_ESP32
    printf("BREADCRUMB 1c\n");
    esp_log_level_set("*", ESP_LOG_NONE); // sump default run on port0 - disable log
#endif
    printf("BREADCRUMB 2\n");
    logic_analyzer_sump();
#endif
    printf("BREADCRUMB 2a\n");
#ifdef CONFIG_ANALYZER_USE_WS
    logic_analyzer_ws_server();
#endif

#ifdef CONFIG_ANALYZER_USE_CLI
#ifdef CONFIG_IDF_TARGET_ESP32
    esp_log_level_set("*", ESP_LOG_NONE); // cli default run on port0 - disable log
#endif
    logic_analyzer_cli();
#endif
    printf("BREADCRUMB 3\n");
    while (1)
    {
        vTaskDelay(100);
    }
}