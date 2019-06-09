#ifndef   _PAINLESS_MESH_STA_H_
#define   _PAINLESS_MESH_STA_H_

#include "painlessmesh/configuration.hpp"

#include <list>

#define SCAN_INTERVAL       10*TASK_SECOND // AP scan period in ms

typedef struct {
  uint8_t bssid[6];
  TSTRING ssid;
  int8_t rssi;
} WiFi_AP_Record_t;

class painlessMesh;

class StationScan {
  public:
    Task task; // Station scanning for connections

    StationScan() {}
    void init(painlessMesh *pMesh, TSTRING &ssid, TSTRING &password,
              uint16_t port);
    void stationScan();
    void scanComplete();
    void filterAPs();
    void connectToAP();

  private:
   TSTRING ssid;
   TSTRING password;
   painlessMesh *mesh;
   uint16_t port;
   std::list<WiFi_AP_Record_t> aps;

   void requestIP(WiFi_AP_Record_t &ap);

   // Manually configure network and ip
   bool manual = false;
   IPAddress manualIP = IPAddress(0, 0, 0, 0);

   friend class painlessMesh;
};

#endif
