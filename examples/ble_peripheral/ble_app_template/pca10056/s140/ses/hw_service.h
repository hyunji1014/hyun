#ifndef hw_SERVICE_H
#define hw_SERVICE_H
 
#include <string.h>
#include "ble.h"
#include "ble_srv_common.h"

#ifndef BLE_HW_BLE_OBSERVER_PRIO
#define BLE_HW_BLE_OBSERVER_PRIO 2
#endif
 
#define BLE_HW_DEF(_name)                                                                         \
static ble_hw_service_t _name;                                                                    \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HW_BLE_OBSERVER_PRIO,                                                    \
                     ble_hw_service_on_ble_evt, &_name)

// hw Service UUID: 03B80E5A-EDE8-4B33-A751-6CE34EC4C700
// hw Data I/O Characteristic UUID: 7772E5DB-3868-4112-A1A9-F2669D106BF3
// test uuid : 
// The bytes need to be in reverse order to match the UUID from the spec
// Note: They are stored in little endian, meaning that the Least Significant Byte
// is stored first.
    
#define BLE_UUID_HW_SERVICE_BASE_UUID  {0x00, 0xC7, 0xC4, 0x4E, 0xE3, 0x6C, 0x51, 0xA7, 0x33, 0x4B, 0xE8, 0xED, 0x5A, 0x0E, 0xB8, 0x03}
#define BLE_UUID_HW_SERVICE_UUID        0x0E5A
    
#define BLE_UUID_HW_DATA_IO_CHAR_BASE_UUID {0xF3, 0x6B, 0x10, 0x9D, 0x66, 0xF2, 0xA9, 0xA1, 0x12, 0x41, 0x68, 0x38, 0xDB, 0xE5, 0x72, 0x77}
#define BLE_UUID_HW_DATA_IO_CHAR_UUID       0xE5DB


/**@brief hw Service event type. */
typedef enum
{
    BLE_DATA_IO_EVT_NOTIFICATION_ENABLED,                             /**&lt; Custom value notification enabled event. */
    BLE_DATA_IO_EVT_NOTIFICATION_DISABLED,                            /**&lt; Custom value notification disabled event. */
} ble_hw_evt_type_t;
 
/**@brief hw Service event. */
typedef struct{
  ble_hw_evt_type_t evt_type;
} ble_hw_evt_t;

// Forward declaration of the ble_hw_service_t type. 
typedef struct ble_hw_service_s ble_hw_service_t;

// Define the hw Data I/O write handler function
typedef void (*ble_hw_evt_handler_t) (ble_hw_service_t * p_hw_service, ble_hw_evt_t * p_evt);

// Define the init data structure that is used to configure a callback function that can be called back to the main application
typedef struct
{
    ble_hw_evt_handler_t evt_handler;  /**&lt; Event handler to be called when a hw event occurs. */
} ble_hw_service_init_t;

/**@brief hw Service structure. This contains various status information for the service. */
struct ble_hw_service_s
{
    uint16_t                    service_handle;
    ble_gatts_char_handles_t    data_io_char_handles;
    uint8_t                     uuid_type;
    uint16_t                    conn_handle;
    ble_hw_evt_handler_t        evt_handler;
};

/**@brief Function for initializing the hw Service.
 *
 * @param[out]  p_hw_service   hw Service structure. This structure will have to be supplied by
 *                               the application. It will be initialized by this function, and will later
 *                               be used to identify this particular service instance.
 * @param[in]   p_hw_service_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_hw_service_init(ble_hw_service_t * p_hw_service, const ble_hw_service_init_t * p_hw_service_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the hw Service.
 *
 *
 * @param[in]   p_hw_service      LED Button Service structure.
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 */
void ble_hw_service_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);

#endif /* hw_SERVICE_H */