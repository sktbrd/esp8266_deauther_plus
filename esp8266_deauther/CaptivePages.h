#pragma once
#include <Arduino.h>

extern const char PAGE_STEP1[] PROGMEM;
extern const char PAGE_STEP2[] PROGMEM;
extern const char PAGE_DONE[]  PROGMEM;

const char PAGE_STEP1[] PROGMEM = R"HTML(
<!doctype html><html><head>
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Training Login – Step 1</title>
<style>
 body{font-family:system-ui,Arial,sans-serif;margin:0;background:#f7f7f9}
 .banner{background:#ffe9a8;padding:.6rem 1rem;border-bottom:1px solid #e7c865}
 .wrap{max-width:420px;margin:2rem auto;background:#fff;border:1px solid #ddd;border-radius:10px;
       box-shadow:0 2px 10px rgba(0,0,0,.06);padding:1.2rem}
 h1{font-size:1.1rem;margin:.4rem 0 1rem}
 input,button{width:100%;font-size:1rem;padding:.7rem;margin:.35rem 0}
 .muted{color:#666;font-size:.9rem}
</style></head><body>
<div class="banner"><strong>Simulation:</strong> Training portal. Do not use real passwords.</div>
<div class="wrap">
  <h1>Sign in – Step 1 of 2</h1>
  <form action="/step1" method="post">
    <input name="email" placeholder="Email or username" autofocus required>
    <button type="submit">Next</button>
  </form>
  <p class="muted">This is a classroom simulation to learn safe browsing.</p>
</div>
</body></html>
)HTML";

const char PAGE_STEP2[] PROGMEM = R"HTML(
<!doctype html><html><head>
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Training Login – Step 2</title>
<style>
 body{font-family:system-ui,Arial,sans-serif;margin:0;background:#f7f7f9}
 .banner{background:#ffe9a8;padding:.6rem 1rem;border-bottom:1px solid #e7c865}
 .wrap{max-width:420px;margin:2rem auto;background:#fff;border:1px solid #ddd;border-radius:10px;
       box-shadow:0 2px 10px rgba(0,0,0,.06);padding:1.2rem}
 h1{font-size:1.1rem;margin:.4rem 0 1rem}
 input,button{width:100%;font-size:1rem;padding:.7rem;margin:.35rem 0}
 .muted{color:#666;font-size:.9rem}
</style></head><body>
<div class="banner"><strong>Simulation:</strong> Training portal. Do not use real passwords.</div>
<div class="wrap">
  <h1>Welcome<span id="who"></span></h1>
  <form action="/step2" method="post">
    <input name="password" type="password" placeholder="Password" autofocus required>
    <button type="submit">Sign in</button>
  </form>
  <p class="muted">Never enter real passwords on unfamiliar portals or open Wi-Fi.</p>
</div>
<script>
  const params=new URLSearchParams(location.search); 
  const e=params.get('e'); if(e){document.getElementById('who').textContent=' '+e;}
</script>
</body></html>
)HTML";

const char PAGE_DONE[] PROGMEM = R"HTML(
<!doctype html><html><head>
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Training Complete</title>
<style>
 body{font-family:system-ui,Arial,sans-serif;margin:0;background:#f7f7f9}
 .wrap{max-width:520px;margin:2rem auto;background:#fff;border:1px solid #ddd;border-radius:10px;
       box-shadow:0 2px 10px rgba(0,0,0,.06);padding:1.2rem}
 h1{font-size:1.2rem;margin:.4rem 0 1rem}
 li{margin:.4rem 0}
</style></head><body>
<div class="wrap">
  <h1>Simulation complete</h1>
  <p>You just entered credentials into a training page. A real attacker could capture them.</p>
  <ul>
    <li>Always check the URL and certificate (HTTPS padlock is not enough—check the domain).</li>
    <li>Prefer mobile hotspots/VPN over open public Wi-Fi.</li>
    <li>Enable multi-factor authentication.</li>
  </ul>
</div>
</body></html>
)HTML";
