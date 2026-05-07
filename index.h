#ifndef INDEX_H
#define INDEX_H

// Edj20 Industrial IoT Edge Device — Test Dashboard
// Wimera Systems
//
// AP+STA mode: all fetch() calls use relative paths (e.g. "/api/di").
// The browser targets whatever IP it used to load the page, so this works
// correctly whether the client joined via the device's own AP (192.168.4.x)
// or reached the device through the STA-side network. Never hardcode an IP.

static const char INDEX_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>EDJ20 | Wimera Systems — Test Dashboard</title>
<link href="https://fonts.googleapis.com/css2?family=Share+Tech+Mono&family=Rajdhani:wght@400;500;600;700&family=Barlow+Condensed:wght@300;400;600;700&display=swap" rel="stylesheet">
<style>
  :root {
    --bg-root:    #070c12;
    --bg-panel:   #0c1520;
    --bg-card:    #101b28;
    --bg-card2:   #131f2e;
    --accent:     #00c8ff;
    --accent2:    #006fa8;
    --green:      #00ff88;
    --red:        #ff3a3a;
    --yellow:     #ffcc00;
    --text:       #d8eaf8;
    --text-dim:   #4a6a88;
    --text-label: #7a9fbe;
    --border:     #192840;
    --border-hi:  #1e4060;
    --grid:       rgba(0,200,255,0.03);
  }
  *{margin:0;padding:0;box-sizing:border-box;}
  body{
    font-family:'Barlow Condensed',sans-serif;
    background:var(--bg-root);color:var(--text);
    min-height:100vh;overflow-x:hidden;
  }
  body::before{
    content:'';position:fixed;inset:0;
    background-image:
      linear-gradient(var(--grid) 1px,transparent 1px),
      linear-gradient(90deg,var(--grid) 1px,transparent 1px);
    background-size:40px 40px;pointer-events:none;z-index:0;
  }

  /* ── HEADER ── */
  header{
    position:relative;z-index:20;
    background:var(--bg-panel);border-bottom:1px solid var(--border);
    padding:0 28px;height:64px;
    display:flex;align-items:center;justify-content:space-between;
  }
  .logo-block{display:flex;align-items:center;gap:14px;}
  .wimera-logo{width:40px;height:40px;flex-shrink:0;}
  .brand-text{display:flex;flex-direction:column;line-height:1.15;}
  .brand-name{font-family:'Rajdhani',sans-serif;font-weight:700;font-size:18px;color:var(--accent);letter-spacing:2.5px;text-transform:uppercase;}
  .brand-sub{font-size:11px;color:var(--text-dim);letter-spacing:1.5px;text-transform:uppercase;}
  .header-center{position:absolute;left:50%;transform:translateX(-50%);display:flex;flex-direction:column;align-items:center;}
  .device-name{font-family:'Share Tech Mono',monospace;font-size:22px;color:var(--text);letter-spacing:5px;}
  .device-tag{font-size:11px;color:var(--text-dim);letter-spacing:2px;text-transform:uppercase;margin-top:2px;}
  .header-right{display:flex;align-items:center;gap:22px;}
  .conn-status{display:flex;align-items:center;gap:7px;font-family:'Share Tech Mono',monospace;font-size:11px;color:var(--text-dim);letter-spacing:1px;}
  .conn-dot{width:9px;height:9px;border-radius:50%;background:var(--green);box-shadow:0 0 8px var(--green);animation:pulse-dot 2s ease infinite;}
  .conn-dot.off{background:var(--red);box-shadow:0 0 8px var(--red);animation:none;}
  @keyframes pulse-dot{0%,100%{opacity:1}50%{opacity:.35}}
  .sys-time{font-family:'Share Tech Mono',monospace;font-size:14px;color:var(--accent);letter-spacing:2px;}

  /* ── STATUS BAR ── */
  .status-bar{
    position:relative;z-index:15;
    background:rgba(0,200,255,0.03);border-bottom:1px solid var(--border);
    padding:0 28px;height:38px;display:flex;align-items:center;gap:30px;
  }
  .sb-item{display:flex;align-items:center;gap:7px;font-size:11px;letter-spacing:1px;color:var(--text-dim);text-transform:uppercase;}
  .sb-item .v{font-family:'Share Tech Mono',monospace;color:var(--text);font-size:11px;}
  .sb-pill{padding:2px 10px;border-radius:2px;font-family:'Share Tech Mono',monospace;font-size:10px;letter-spacing:1px;background:rgba(255,204,0,.1);color:var(--yellow);border:1px solid rgba(255,204,0,.22);}
  .sb-pill.running{background:rgba(0,200,255,.12);color:var(--accent);border-color:rgba(0,200,255,.25);animation:bpulse 1s ease infinite;}
  .sb-pill.complete{background:rgba(0,255,136,.12);color:var(--green);border-color:rgba(0,255,136,.25);animation:none;}
  .sb-pill.error{background:rgba(255,58,58,.12);color:var(--red);border-color:rgba(255,58,58,.25);animation:none;}
  @keyframes bpulse{0%,100%{opacity:1}50%{opacity:.5}}

  /* ── LAYOUT ── */
  .layout{position:relative;z-index:5;display:grid;grid-template-columns:260px 1fr 260px;min-height:calc(100vh - 140px);}

  /* ── SIDEBAR ── */
  .sidebar{background:var(--bg-panel);border-right:1px solid var(--border);padding:18px 14px;display:flex;flex-direction:column;gap:14px;overflow-y:auto;}
  .sidebar.right{border-right:none;border-left:1px solid var(--border);}
  .sec-title{font-family:'Share Tech Mono',monospace;font-size:10px;color:var(--accent);letter-spacing:3px;text-transform:uppercase;padding-bottom:9px;border-bottom:1px solid var(--border);}

  /* card */
  .card{background:var(--bg-card);border:1px solid var(--border);border-radius:3px;padding:13px;}
  .card-title{font-size:10px;letter-spacing:2px;text-transform:uppercase;color:var(--text-dim);margin-bottom:11px;display:flex;align-items:center;gap:6px;}
  .card-title::before{content:'';width:3px;height:11px;background:var(--accent);display:block;flex-shrink:0;}

  /* DI channel boxes */
  .ch-grid{display:grid;grid-template-columns:1fr 1fr;gap:7px;}
  .ch-box{background:var(--bg-card2);border:1px solid var(--border);border-radius:3px;padding:9px 10px;display:flex;flex-direction:column;gap:5px;transition:border-color .25s,background .25s;}
  .ch-box.hi{border-color:var(--green);background:rgba(0,255,136,.04);}
  .ch-lbl{font-family:'Share Tech Mono',monospace;font-size:10px;color:var(--text-dim);letter-spacing:1px;}
  .ch-val{font-family:'Share Tech Mono',monospace;font-size:15px;font-weight:700;letter-spacing:2px;color:var(--text-dim);}
  .ch-val.hi{color:var(--green);text-shadow:0 0 8px rgba(0,255,136,.4);}
  .ch-bar{height:3px;background:var(--border);border-radius:1px;overflow:hidden;}
  .ch-bar-fill{height:100%;width:0%;background:var(--green);transition:width .3s;}

  /* DO buttons */
  .do-row{display:flex;align-items:center;justify-content:space-between;padding:7px 0;border-bottom:1px solid rgba(25,40,64,.6);}
  .do-row:last-child{border-bottom:none;}
  .do-lbl{font-family:'Share Tech Mono',monospace;font-size:11px;color:var(--text-label);letter-spacing:1px;}
  .do-btns{display:flex;gap:4px;}
  .tbtn{padding:4px 12px;border-radius:2px;border:1px solid var(--border);background:transparent;font-family:'Share Tech Mono',monospace;font-size:10px;letter-spacing:1px;cursor:pointer;color:var(--text-dim);transition:all .15s;}
  .tbtn.on.active,.tbtn.on:hover{background:rgba(0,255,136,.15);border-color:var(--green);color:var(--green);}
  .tbtn.off.active,.tbtn.off:hover{background:rgba(255,58,58,.12);border-color:var(--red);color:var(--red);}

  /* LED control */
  .led-row{display:flex;align-items:center;justify-content:space-between;padding:7px 0;border-bottom:1px solid rgba(25,40,64,.6);}
  .led-row:last-child{border-bottom:none;}
  .led-lbl{font-family:'Share Tech Mono',monospace;font-size:11px;color:var(--text-label);letter-spacing:1px;display:flex;align-items:center;gap:8px;}
  .led-dot{width:11px;height:11px;border-radius:50%;background:#0a1520;border:1px solid var(--border);transition:all .3s;}
  .led-dot.on-green{background:var(--green);border-color:var(--green);box-shadow:0 0 8px var(--green);}
  .led-dot.on-blue{background:var(--accent);border-color:var(--accent);box-shadow:0 0 8px var(--accent);}
  .led-dot.blink{animation:led-blink .55s ease infinite;}
  @keyframes led-blink{0%,100%{opacity:1}50%{opacity:.08}}
  .led-ctrls{display:flex;gap:4px;}
  .lbtn{padding:3px 8px;border:1px solid var(--border);background:transparent;color:var(--text-dim);font-family:'Share Tech Mono',monospace;font-size:9px;cursor:pointer;letter-spacing:1px;border-radius:2px;transition:all .15s;}
  .lbtn:hover,.lbtn.active{border-color:var(--accent);color:var(--accent);}

  /* Analog meter */
  .meter-row{display:flex;align-items:center;gap:9px;padding:7px 0;border-bottom:1px solid rgba(25,40,64,.5);}
  .meter-row:last-child{border-bottom:none;}
  .meter-name{font-family:'Share Tech Mono',monospace;font-size:10px;color:var(--text-dim);width:34px;flex-shrink:0;letter-spacing:1px;}
  .meter-track{flex:1;height:7px;background:var(--border);border-radius:1px;overflow:hidden;}
  .meter-fill{height:100%;background:linear-gradient(90deg,var(--accent2),var(--accent));transition:width .4s;box-shadow:0 0 6px rgba(0,200,255,.3);}
  .meter-val{font-family:'Share Tech Mono',monospace;font-size:12px;color:var(--accent);width:50px;text-align:right;flex-shrink:0;}

  /* Modbus stats */
  .mb-stat{display:flex;align-items:center;justify-content:space-between;padding:7px 0;border-bottom:1px solid rgba(25,40,64,.5);}
  .mb-stat:last-child{border-bottom:none;}
  .mb-key{font-family:'Share Tech Mono',monospace;font-size:10px;color:var(--text-dim);letter-spacing:1px;}
  .mb-val{font-family:'Share Tech Mono',monospace;font-size:11px;color:var(--text);letter-spacing:1px;}

  /* ── CENTER ── */
  .center{padding:20px 22px;display:flex;flex-direction:column;gap:18px;overflow-y:auto;}

  /* Test control banner */
  .test-banner{background:var(--bg-card);border:1px solid var(--border);border-radius:3px;padding:16px 20px;display:flex;align-items:center;gap:18px;}
  .tb-progress{flex:1;}
  .tb-prog-labels{display:flex;justify-content:space-between;font-size:11px;color:var(--text-dim);letter-spacing:1px;text-transform:uppercase;margin-bottom:7px;}
  .tb-bar-track{height:5px;background:var(--border);border-radius:1px;overflow:hidden;}
  .tb-bar-fill{height:100%;width:0%;background:linear-gradient(90deg,var(--accent2),var(--accent));border-radius:1px;transition:width .5s ease;box-shadow:0 0 10px rgba(0,200,255,.4);}
  .tb-stage{font-family:'Share Tech Mono',monospace;font-size:12px;color:var(--accent);letter-spacing:2px;min-width:200px;}
  .tb-stage small{color:var(--text-dim);font-size:10px;display:block;margin-top:2px;letter-spacing:1px;}
  .btn-run{padding:10px 26px;background:linear-gradient(135deg,var(--accent2),var(--accent));color:#000;border:none;border-radius:3px;font-family:'Rajdhani',sans-serif;font-weight:700;font-size:14px;letter-spacing:3px;text-transform:uppercase;cursor:pointer;transition:all .2s;white-space:nowrap;}
  .btn-run:hover{box-shadow:0 0 20px rgba(0,200,255,.45);transform:translateY(-1px);}
  .btn-run:active{transform:none;}
  .btn-run:disabled{opacity:.35;cursor:not-allowed;transform:none;box-shadow:none;}
  .btn-stop{padding:10px 20px;background:rgba(255,58,58,.1);color:var(--red);border:1px solid rgba(255,58,58,.28);border-radius:3px;font-family:'Rajdhani',sans-serif;font-weight:700;font-size:14px;letter-spacing:2px;text-transform:uppercase;cursor:pointer;transition:all .2s;}
  .btn-stop:hover{background:rgba(255,58,58,.2);}

  /* Module cards */
  .module-grid{display:grid;grid-template-columns:1fr 1fr 1fr;gap:12px;}
  .mod-card{background:var(--bg-card);border:1px solid var(--border);border-radius:3px;padding:14px;display:flex;flex-direction:column;gap:10px;position:relative;overflow:hidden;transition:border-color .3s;animation:fade-up .3s ease backwards;}
  @keyframes fade-up{from{opacity:0;transform:translateY(6px)}to{opacity:1;transform:none}}
  .mod-card::after{content:'';position:absolute;top:0;left:0;right:0;height:2px;background:var(--border);transition:background .3s;}
  .mod-card.pass{border-color:rgba(0,255,136,.22);}
  .mod-card.pass::after{background:var(--green);}
  .mod-card.fail{border-color:rgba(255,58,58,.22);}
  .mod-card.fail::after{background:var(--red);}
  .mod-card.active{border-color:rgba(0,200,255,.3);}
  .mod-card.active::after{background:linear-gradient(90deg,transparent,var(--accent),transparent);background-size:200% 100%;animation:sweep 1.4s ease infinite;}
  @keyframes sweep{0%{background-position:-200% 0}100%{background-position:200% 0}}
  .mod-hdr{display:flex;align-items:center;justify-content:space-between;}
  .mod-name{font-family:'Rajdhani',sans-serif;font-weight:700;font-size:15px;letter-spacing:2px;text-transform:uppercase;}
  .badge{padding:2px 8px;border-radius:2px;font-family:'Share Tech Mono',monospace;font-size:9px;letter-spacing:1px;text-transform:uppercase;}
  .b-pend{background:rgba(74,106,136,.12);color:var(--text-dim);border:1px solid var(--border);}
  .b-act{background:rgba(0,200,255,.1);color:var(--accent);border:1px solid rgba(0,200,255,.22);animation:bpulse 1s ease infinite;}
  .b-pass{background:rgba(0,255,136,.1);color:var(--green);border:1px solid rgba(0,255,136,.22);}
  .b-fail{background:rgba(255,58,58,.1);color:var(--red);border:1px solid rgba(255,58,58,.22);}
  .mod-chips{display:flex;flex-wrap:wrap;gap:4px;}
  .chip{padding:2px 8px;background:var(--bg-card2);border:1px solid var(--border);border-radius:2px;font-family:'Share Tech Mono',monospace;font-size:9px;color:var(--text-dim);letter-spacing:1px;transition:all .2s;}
  .chip.ok{border-color:rgba(0,255,136,.3);color:var(--green);background:rgba(0,255,136,.05);}
  .chip.err{border-color:rgba(255,58,58,.3);color:var(--red);background:rgba(255,58,58,.05);}
  .chip.testing{border-color:rgba(0,200,255,.4);color:var(--accent);animation:bpulse .7s ease infinite;}
  .mod-msg{font-family:'Share Tech Mono',monospace;font-size:10px;color:var(--text-dim);letter-spacing:1px;min-height:16px;}

  /* Log */
  .log-panel{background:var(--bg-card);border:1px solid var(--border);border-radius:3px;overflow:hidden;}
  .log-hdr{padding:9px 13px;border-bottom:1px solid var(--border);display:flex;align-items:center;justify-content:space-between;}
  .log-title{font-family:'Share Tech Mono',monospace;font-size:10px;color:var(--accent);letter-spacing:3px;text-transform:uppercase;}
  .log-clr{font-family:'Share Tech Mono',monospace;font-size:9px;color:var(--text-dim);background:none;border:1px solid var(--border);padding:2px 9px;cursor:pointer;letter-spacing:1px;border-radius:2px;transition:all .15s;}
  .log-clr:hover{border-color:var(--accent);color:var(--accent);}
  .log-body{height:160px;overflow-y:auto;padding:9px 13px;font-family:'Share Tech Mono',monospace;font-size:10px;line-height:1.9;}
  .log-body::-webkit-scrollbar{width:3px;}
  .log-body::-webkit-scrollbar-track{background:var(--bg-root);}
  .log-body::-webkit-scrollbar-thumb{background:var(--border-hi);border-radius:2px;}
  .log-entry{display:flex;gap:10px;}
  .log-ts{color:var(--text-dim);flex-shrink:0;}
  .log-m.info{color:var(--text-label);}
  .log-m.ok{color:var(--green);}
  .log-m.err{color:var(--red);}
  .log-m.warn{color:var(--yellow);}
  .log-m.cmd{color:var(--accent);}

  /* Report table */
  .rpt-tbl{width:100%;border-collapse:collapse;}
  .rpt-tbl th{font-family:'Share Tech Mono',monospace;font-size:9px;color:var(--text-dim);letter-spacing:2px;text-transform:uppercase;text-align:left;padding:5px 9px;border-bottom:1px solid var(--border);}
  .rpt-tbl td{font-family:'Share Tech Mono',monospace;font-size:10px;color:var(--text);padding:6px 9px;border-bottom:1px solid rgba(25,40,64,.4);}
  .rpt-tbl tr:last-child td{border-bottom:none;}
  .r-pass{color:var(--green);}
  .r-fail{color:var(--red);}
  .r-pend{color:var(--text-dim);}

  /* ── FOOTER ── */
  footer{position:relative;z-index:20;background:var(--bg-panel);border-top:1px solid var(--border);padding:9px 28px;display:flex;align-items:center;justify-content:space-between;font-size:10px;color:var(--text-dim);letter-spacing:1px;}
  .ft-left{display:flex;gap:24px;}
  .ft-item{display:flex;gap:6px;align-items:center;}
  .ft-item .k{color:var(--text-dim);text-transform:uppercase;}
  .ft-item .v{font-family:'Share Tech Mono',monospace;color:var(--text-label);}
</style>
</head>
<body>

<!-- ═══ HEADER ═══ -->
<header>
  <div class="logo-block">
    <svg class="wimera-logo" viewBox="0 0 80 80" fill="none" xmlns="http://www.w3.org/2000/svg">
      <rect width="80" height="80" rx="7" fill="#0c1520"/>
      <rect x="1" y="1" width="78" height="78" rx="6" stroke="#00c8ff" stroke-width="1.2" stroke-opacity="0.35"/>
      <polyline points="10,22 21,56 33,34 45,56 56,22" stroke="#00c8ff" stroke-width="4" stroke-linecap="round" stroke-linejoin="round" fill="none"/>
      <circle cx="10" cy="22" r="3.5" fill="#00c8ff"/>
      <circle cx="21" cy="56" r="3.5" fill="#00c8ff"/>
      <circle cx="33" cy="34" r="3.5" fill="#00c8ff"/>
      <circle cx="45" cy="56" r="3.5" fill="#00c8ff"/>
      <circle cx="56" cy="22" r="3.5" fill="#00c8ff"/>
      <line x1="8" y1="66" x2="72" y2="66" stroke="#00c8ff" stroke-width="0.8" stroke-opacity="0.25"/>
      <text x="40" y="75" text-anchor="middle" font-family="monospace" font-size="6.5" fill="#00c8ff" fill-opacity="0.55" letter-spacing="2">WIMERA</text>
    </svg>
    <div class="brand-text">
      <span class="brand-name">Wimera Systems</span>
      <span class="brand-sub">Industrial IoT Solutions</span>
    </div>
  </div>

  <div class="header-center">
    <div class="device-name">EDJ20</div>
    <div class="device-tag">IIoT Edge Device &mdash; Test Dashboard</div>
  </div>

  <div class="header-right">
    <div class="conn-status">
      <div class="conn-dot" id="connDot"></div>
      <span id="connLabel">AP+STA</span>
    </div>
    <div class="sys-time" id="sysTime">--:--:--</div>
  </div>
</header>

<!-- ═══ STATUS BAR ═══ -->
<div class="status-bar">
  <div class="sb-item">Device <span class="v">EDJ20-001</span></div>
  <div class="sb-item">FW <span class="v">1.0.0</span></div>
  <div class="sb-item">SoC <span class="v">ESP32-S3</span></div>
  <div class="sb-item">ESP-IDF <span class="v">v5.1.2</span></div>
  <div class="sb-item">Mode <span class="v">AP+STA</span></div>
  <div class="sb-item">IP <span class="v" id="devIP">---</span></div>
  <div class="sb-item">Test <span class="sb-pill" id="testPill">IDLE</span></div>
</div>

<!-- ═══ MAIN LAYOUT ═══ -->
<div class="layout">

  <!-- ── LEFT SIDEBAR ── -->
  <div class="sidebar">
    <div class="sec-title">// Digital Inputs</div>
    <div class="card">
      <div class="card-title">DI Channels &mdash; 24V</div>
      <div class="ch-grid">
        <div class="ch-box" id="diBox_1"><div class="ch-lbl">DI1</div><div class="ch-val" id="diVal_1">LOW</div><div class="ch-bar"><div class="ch-bar-fill" id="diBar_1"></div></div></div>
        <div class="ch-box" id="diBox_2"><div class="ch-lbl">DI2</div><div class="ch-val" id="diVal_2">LOW</div><div class="ch-bar"><div class="ch-bar-fill" id="diBar_2"></div></div></div>
        <div class="ch-box" id="diBox_3"><div class="ch-lbl">DI3</div><div class="ch-val" id="diVal_3">LOW</div><div class="ch-bar"><div class="ch-bar-fill" id="diBar_3"></div></div></div>
        <div class="ch-box" id="diBox_4"><div class="ch-lbl">DI4</div><div class="ch-val" id="diVal_4">LOW</div><div class="ch-bar"><div class="ch-bar-fill" id="diBar_4"></div></div></div>
      </div>
    </div>

    <div class="sec-title">// Digital Outputs</div>
    <div class="card">
      <div class="card-title">DO Channels &mdash; 24V</div>
      <div class="do-row">
        <span class="do-lbl">DO1</span>
        <div class="do-btns">
          <button class="tbtn on"       id="do1On"  onclick="setDO(1,1)">ON</button>
          <button class="tbtn off active" id="do1Off" onclick="setDO(1,0)">OFF</button>
        </div>
      </div>
      <div class="do-row">
        <span class="do-lbl">DO2</span>
        <div class="do-btns">
          <button class="tbtn on"       id="do2On"  onclick="setDO(2,1)">ON</button>
          <button class="tbtn off active" id="do2Off" onclick="setDO(2,0)">OFF</button>
        </div>
      </div>
    </div>

    <div class="sec-title">// Analog Inputs</div>
    <div class="card">
      <div class="card-title">AI Channels &mdash; 0&ndash;3.3V</div>
      <div class="meter-row">
        <div class="meter-name">AI1</div>
        <div class="meter-track"><div class="meter-fill" id="aiFill_1" style="width:0%"></div></div>
        <div class="meter-val" id="aiVal_1">0.00V</div>
      </div>
      <div class="meter-row">
        <div class="meter-name">AI2</div>
        <div class="meter-track"><div class="meter-fill" id="aiFill_2" style="width:0%"></div></div>
        <div class="meter-val" id="aiVal_2">0.00V</div>
      </div>
    </div>
  </div><!-- /left sidebar -->

  <!-- ── CENTER ── -->
  <div class="center">

    <!-- Test Control Banner -->
    <div class="test-banner">
      <div class="tb-stage">
        <span id="stageLabel">READY TO TEST</span>
        <small id="stageDesc">All interfaces idle. Press RUN TEST to begin.</small>
      </div>
      <div class="tb-progress">
        <div class="tb-prog-labels">
          <span>Test Progress</span>
          <span id="progPct">0%</span>
        </div>
        <div class="tb-bar-track">
          <div class="tb-bar-fill" id="progBar"></div>
        </div>
      </div>
      <button class="btn-run" id="btnRun" onclick="startTest()">&#9654;&nbsp; RUN TEST</button>
      <button class="btn-stop" onclick="stopTest()">&#9632;&nbsp; STOP</button>
    </div>

    <!-- Module Cards -->
    <div class="module-grid">

      <div class="mod-card" id="mod_di" style="animation-delay:.05s">
        <div class="mod-hdr"><span class="mod-name">Digital In</span><span class="badge b-pend" id="badge_di">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_di_1">DI1</span>
          <span class="chip" id="chip_di_2">DI2</span>
          <span class="chip" id="chip_di_3">DI3</span>
          <span class="chip" id="chip_di_4">DI4</span>
        </div>
        <div class="mod-msg" id="msg_di">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_do" style="animation-delay:.10s">
        <div class="mod-hdr"><span class="mod-name">Digital Out</span><span class="badge b-pend" id="badge_do">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_do_1">DO1</span>
          <span class="chip" id="chip_do_2">DO2</span>
        </div>
        <div class="mod-msg" id="msg_do">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_ai" style="animation-delay:.15s">
        <div class="mod-hdr"><span class="mod-name">Analog In</span><span class="badge b-pend" id="badge_ai">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_ai_1">AI1</span>
          <span class="chip" id="chip_ai_2">AI2</span>
        </div>
        <div class="mod-msg" id="msg_ai">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_mb" style="animation-delay:.20s">
        <div class="mod-hdr"><span class="mod-name">Modbus RTU</span><span class="badge b-pend" id="badge_mb">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_mb_ap">A+</span>
          <span class="chip" id="chip_mb_bn">B-</span>
        </div>
        <div class="mod-msg" id="msg_mb">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_ct" style="animation-delay:.25s">
        <div class="mod-hdr"><span class="mod-name">CT Sensors</span><span class="badge b-pend" id="badge_ct">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_ct_1">CT1</span>
          <span class="chip" id="chip_ct_2">CT2</span>
          <span class="chip" id="chip_ct_3">CT3</span>
        </div>
        <div class="mod-msg" id="msg_ct">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_led" style="animation-delay:.30s">
        <div class="mod-hdr"><span class="mod-name">LED Control</span><span class="badge b-pend" id="badge_led">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_led_2">LED2</span>
          <span class="chip" id="chip_led_3">LED3</span>
        </div>
        <div class="mod-msg" id="msg_led">Awaiting test start...</div>
      </div>

    </div><!-- /module-grid -->

    <!-- Event Log -->
    <div class="log-panel">
      <div class="log-hdr">
        <span class="log-title">// Event Log</span>
        <button class="log-clr" onclick="clearLog()">CLR</button>
      </div>
      <div class="log-body" id="logBody">
        <div class="log-entry"><span class="log-ts" id="initTs"></span><span class="log-m info">System initialised. Awaiting test sequence.</span></div>
      </div>
    </div>

  </div><!-- /center -->

  <!-- ── RIGHT SIDEBAR ── -->
  <div class="sidebar right">
    <div class="sec-title">// LED Control</div>
    <div class="card">
      <div class="card-title">Status LEDs</div>
      <!-- LED1: power-only, no controls -->
      <div class="led-row">
        <div class="led-lbl"><div class="led-dot on-green" id="led1Dot"></div>LED1</div>
        <span style="font-family:'Share Tech Mono',monospace;font-size:9px;color:var(--text-dim);letter-spacing:1px;">POWER</span>
      </div>
      <!-- LED2: configurable -->
      <div class="led-row">
        <div class="led-lbl"><div class="led-dot" id="led2Dot"></div>LED2</div>
        <div class="led-ctrls">
          <button class="lbtn" onclick="setLED(2,'on')">ON</button>
          <button class="lbtn" onclick="setLED(2,'off')">OFF</button>
          <button class="lbtn" onclick="setLED(2,'blink')">BLK</button>
        </div>
      </div>
      <!-- LED3: configurable -->
      <div class="led-row">
        <div class="led-lbl"><div class="led-dot" id="led3Dot"></div>LED3</div>
        <div class="led-ctrls">
          <button class="lbtn" onclick="setLED(3,'on')">ON</button>
          <button class="lbtn" onclick="setLED(3,'off')">OFF</button>
          <button class="lbtn" onclick="setLED(3,'blink')">BLK</button>
        </div>
      </div>
    </div>

    <div class="sec-title">// Modbus RTU</div>
    <div class="card">
      <div class="card-title">Interface Status</div>
      <div class="mb-stat"><span class="mb-key">LINES</span><span class="mb-val">A+ / B-</span></div>
      <div class="mb-stat"><span class="mb-key">PROTOCOL</span><span class="mb-val">RTU</span></div>
      <div class="mb-stat"><span class="mb-key">BAUD</span><span class="mb-val" id="mbBaud">9600</span></div>
      <div class="mb-stat"><span class="mb-key">LAST TX</span><span class="mb-val" id="mbLastTx">---</span></div>
      <div class="mb-stat"><span class="mb-key">LAST RX</span><span class="mb-val" id="mbLastRx">---</span></div>
      <div class="mb-stat"><span class="mb-key">STATUS</span><span class="mb-val" id="mbStatus">IDLE</span></div>
    </div>

    <div class="sec-title">// CT Sensors</div>
    <div class="card">
      <div class="card-title">AC Current &mdash; Non-invasive</div>
      <div class="meter-row">
        <div class="meter-name">CT1</div>
        <div class="meter-track"><div class="meter-fill" id="ctFill_1" style="width:0%"></div></div>
        <div class="meter-val" id="ctVal_1">0.0A</div>
      </div>
      <div class="meter-row">
        <div class="meter-name">CT2</div>
        <div class="meter-track"><div class="meter-fill" id="ctFill_2" style="width:0%"></div></div>
        <div class="meter-val" id="ctVal_2">0.0A</div>
      </div>
      <div class="meter-row">
        <div class="meter-name">CT3</div>
        <div class="meter-track"><div class="meter-fill" id="ctFill_3" style="width:0%"></div></div>
        <div class="meter-val" id="ctVal_3">0.0A</div>
      </div>
    </div>

    <div class="sec-title">// Test Report</div>
    <div class="card">
      <div class="card-title">Pass / Fail Summary</div>
      <table class="rpt-tbl">
        <thead><tr><th>Module</th><th>Ch</th><th>Result</th></tr></thead>
        <tbody>
          <tr><td>Digital In</td> <td>4</td><td class="r-pend" id="rpt_di">—</td></tr>
          <tr><td>Digital Out</td><td>2</td><td class="r-pend" id="rpt_do">—</td></tr>
          <tr><td>Analog In</td>  <td>2</td><td class="r-pend" id="rpt_ai">—</td></tr>
          <tr><td>Modbus RTU</td> <td>1</td><td class="r-pend" id="rpt_mb">—</td></tr>
          <tr><td>CT Sensors</td> <td>3</td><td class="r-pend" id="rpt_ct">—</td></tr>
          <tr><td>LEDs</td>       <td>2</td><td class="r-pend" id="rpt_led">—</td></tr>
        </tbody>
      </table>
    </div>
  </div><!-- /right sidebar -->

</div><!-- /layout -->

<!-- ═══ FOOTER ═══ -->
<footer>
  <div class="ft-left">
    <div class="ft-item"><span class="k">Device</span><span class="v">EDJ20-001</span></div>
    <div class="ft-item"><span class="k">SoC</span><span class="v">ESP32-S3</span></div>
    <div class="ft-item"><span class="k">ESP-IDF</span><span class="v">v5.1.2</span></div>
    <div class="ft-item"><span class="k">Mode</span><span class="v">AP+STA</span></div>
  </div>
  <span>&copy; 2025 Wimera Systems &mdash; Industrial IoT Solutions</span>
</footer>

<!-- ═══ JAVASCRIPT ═══ -->
<script>
// ─────────────────────────────────────────────────────────────────────────────
// AP+STA DESIGN RULE:
//   All fetch() calls use relative paths — e.g. fetch('/api/di').
//   The browser resolves them relative to window.location.origin, which is the
//   IP the client used to open this page. This means the exact same HTML works
//   whether the device is accessed via its own AP (192.168.4.1) or via the
//   router on the STA network (e.g. 192.168.1.x). Never hardcode an IP here.
// ─────────────────────────────────────────────────────────────────────────────

const POLL_MS = 500;
let pollTimer  = null;
let testActive = false;

const STEPS = [
  { key:'di',  label:'TESTING DI',    desc:'Verifying 24V digital input states on DI1–DI4...' },
  { key:'do',  label:'TESTING DO',    desc:'Toggling DO1 & DO2, verifying physical output states...' },
  { key:'ai',  label:'TESTING AI',    desc:'Reading ADC on AI1 & AI2, checking 0–3.3V range...' },
  { key:'mb',  label:'TESTING MODBUS',desc:'Sending RTU frame via A+/B-, awaiting slave response...' },
  { key:'ct',  label:'TESTING CT',    desc:'Sampling AC current from CT1, CT2, CT3...' },
  { key:'led', label:'TESTING LEDs',  desc:'Cycling LED2 & LED3 through ON / BLINK / OFF...' },
];

const CHIP_MAP = {
  di:  ['di_1','di_2','di_3','di_4'],
  do:  ['do_1','do_2'],
  ai:  ['ai_1','ai_2'],
  mb:  ['mb_ap','mb_bn'],
  ct:  ['ct_1','ct_2','ct_3'],
  led: ['led_2','led_3'],
};

// ── Clock ──
function tickClock(){
  const n = new Date();
  document.getElementById('sysTime').textContent =
    String(n.getHours()).padStart(2,'0')+':'+
    String(n.getMinutes()).padStart(2,'0')+':'+
    String(n.getSeconds()).padStart(2,'0');
}
document.getElementById('initTs').textContent = new Date().toLocaleTimeString();
setInterval(tickClock,1000); tickClock();

// ── Logger ──
function log(msg, cls='info'){
  const body = document.getElementById('logBody');
  const div  = document.createElement('div');
  div.className='log-entry';
  div.innerHTML=`<span class="log-ts">${new Date().toLocaleTimeString()}</span><span class="log-m ${cls}">${msg}</span>`;
  body.appendChild(div);
  body.scrollTop=body.scrollHeight;
}
function clearLog(){ document.getElementById('logBody').innerHTML=''; }

// ── Polling ──
function startPolling(){ if(!pollTimer) pollTimer=setInterval(poll,POLL_MS); }
function stopPolling(){  if(pollTimer){ clearInterval(pollTimer); pollTimer=null; } }

async function poll(){
  // --- DI (relative URL — AP+STA safe) ---
  try {
    const r = await fetch('/api/di');
    if(r.ok){
      const d = await r.json();
      // Expected JSON: {"DI1":0,"DI2":1,"DI3":0,"DI4":0}
      for(let i=1;i<=4;i++){
        const v = d['DI'+i];
        document.getElementById('diBox_'+i).classList.toggle('hi', !!v);
        const el = document.getElementById('diVal_'+i);
        el.textContent = v ? 'HIGH' : 'LOW';
        el.className   = 'ch-val'+(v?' hi':'');
        document.getElementById('diBar_'+i).style.width = v?'100%':'0%';
      }
    }
  }catch(e){}

  // --- AI (relative URL) ---
  try {
    const r = await fetch('/api/ai');
    if(r.ok){
      const d = await r.json();
      // Expected JSON: {"AI1":1.65,"AI2":0.82}  (volts)
      for(let i=1;i<=2;i++){
        const v   = parseFloat(d['AI'+i]||0);
        const pct = Math.min(100,(v/3.3)*100).toFixed(1);
        document.getElementById('aiFill_'+i).style.width = pct+'%';
        document.getElementById('aiVal_'+i).textContent  = v.toFixed(2)+'V';
      }
    }
  }catch(e){}

  // --- CT (relative URL) ---
  try {
    const r = await fetch('/api/ct');
    if(r.ok){
      const d = await r.json();
      // Expected JSON: {"CT1":2.4,"CT2":0.0,"CT3":5.1}  (amps)
      const MAX=20;
      for(let i=1;i<=3;i++){
        const v   = parseFloat(d['CT'+i]||0);
        const pct = Math.min(100,(v/MAX)*100).toFixed(1);
        document.getElementById('ctFill_'+i).style.width = pct+'%';
        document.getElementById('ctVal_'+i).textContent  = v.toFixed(1)+'A';
      }
    }
  }catch(e){}
}

// ── DO Control (relative URL) ──
async function setDO(ch,val){
  try {
    const r = await fetch(`/api/do?ch=${ch}&val=${val}`);
    if(r.ok){
      document.getElementById(`do${ch}On`).classList.toggle('active', !!val);
      document.getElementById(`do${ch}Off`).classList.toggle('active',!val);
      log(`DO${ch} → ${val?'ON':'OFF'}`, 'cmd');
    }
  }catch(e){ log(`DO${ch} command failed`,'err'); }
}

// ── LED Control (relative URL) ──
async function setLED(num,state){
  try {
    const r = await fetch(`/api/led?num=${num}&state=${state}`);
    if(r.ok){
      const dot = document.getElementById(`led${num}Dot`);
      dot.classList.remove('on-green','on-blue','blink');
      if(state==='on')    dot.classList.add('on-blue');
      if(state==='blink') dot.classList.add('on-blue','blink');
      log(`LED${num} → ${state.toUpperCase()}`, 'cmd');
    }
  }catch(e){ log(`LED${num} command failed`,'err'); }
}

// ── Module helpers ──
function setBadge(key,cls,txt){ const e=document.getElementById('badge_'+key); e.className='badge '+cls; e.textContent=txt; }
function setCard(key,cls)    { document.getElementById('mod_'+key).className='mod-card '+cls; }
function setChip(id,cls)     { const e=document.getElementById('chip_'+id); if(e) e.className='chip '+cls; }
function setMsg(key,txt)     { document.getElementById('msg_'+key).textContent=txt; }
function setReport(key,pass) {
  const e=document.getElementById('rpt_'+key);
  e.textContent = pass===null ? '—' : (pass?'PASS':'FAIL');
  e.className   = pass===null ? 'r-pend' : (pass?'r-pass':'r-fail');
}
function setProgress(step){
  const pct = Math.round((step/STEPS.length)*100);
  document.getElementById('progBar').style.width = pct+'%';
  document.getElementById('progPct').textContent  = pct+'%';
  if(step < STEPS.length){
    document.getElementById('stageLabel').textContent = STEPS[step].label;
    document.getElementById('stageDesc').textContent  = STEPS[step].desc;
  } else {
    document.getElementById('stageLabel').textContent = 'TEST COMPLETE';
    document.getElementById('stageDesc').textContent  = 'All interfaces tested. See report panel.';
  }
}

// ── Run one step ──
async function runStep(i){
  const s = STEPS[i];
  setBadge(s.key,'b-act','TESTING');
  setCard(s.key,'active');
  CHIP_MAP[s.key].forEach(id => setChip('chip_'+id,'testing'));
  log('▶ '+s.label, 'cmd');

  let pass = false;
  try {
    // POST to /api/test/<key> — relative URL, AP+STA safe
    const r = await fetch(`/api/test/${s.key}`, {method:'POST'});
    if(r.ok){
      const d = await r.json();
      // Expected: {"pass":true,"message":"All channels OK","channels":{"DI1":true,...}}
      pass = d.pass === true;
      setMsg(s.key, d.message || (pass?'All channels OK':'One or more channels failed'));
      if(d.channels){
        Object.entries(d.channels).forEach(([ch,ok])=>{
          setChip('chip_'+s.key+'_'+ch.toLowerCase().replace(/[^a-z0-9]/g,''), ok?'ok':'err');
        });
      } else {
        CHIP_MAP[s.key].forEach(id => setChip('chip_'+id, pass?'ok':'err'));
      }
    } else {
      setMsg(s.key,'HTTP '+r.status);
      CHIP_MAP[s.key].forEach(id => setChip('chip_'+id,'err'));
    }
  } catch(e){
    setMsg(s.key,'Request failed: '+e.message);
    CHIP_MAP[s.key].forEach(id => setChip('chip_'+id,'err'));
  }

  setBadge(s.key, pass?'b-pass':'b-fail', pass?'PASS':'FAIL');
  setCard(s.key,  pass?'pass':'fail');
  setReport(s.key, pass);
  log((pass?'✔':'✘')+' '+s.label+' → '+(pass?'PASS':'FAIL'), pass?'ok':'err');
  return pass;
}

// ── Full test sequence ──
async function startTest(){
  if(testActive) return;
  testActive = true;
  document.getElementById('btnRun').disabled = true;
  const pill = document.getElementById('testPill');
  pill.className='sb-pill running'; pill.textContent='RUNNING';

  // Reset all modules
  STEPS.forEach(s=>{
    setBadge(s.key,'b-pend','PENDING');
    setCard(s.key,'');
    setReport(s.key, null);
    setMsg(s.key,'Queued...');
    CHIP_MAP[s.key].forEach(id=>setChip('chip_'+id,''));
  });
  document.getElementById('progBar').style.width='0%';
  document.getElementById('progPct').textContent='0%';

  // LED2 ON = test in progress (per Edj20 spec)
  await setLED(2,'on');
  log('Test sequence started — LED2 ON', 'info');

  let allPass = true;
  for(let i=0;i<STEPS.length;i++){
    if(!testActive) break;
    setProgress(i);
    const ok = await runStep(i);
    if(!ok) allPass = false;
    await new Promise(r=>setTimeout(r,350));
  }

  setProgress(STEPS.length);

  // LED2 OFF = test complete (per Edj20 spec)
  await setLED(2,'off');
  log('Test sequence complete — LED2 OFF', 'info');

  pill.className = allPass?'sb-pill complete':'sb-pill error';
  pill.textContent = allPass?'PASS':'FAIL';
  testActive = false;
  document.getElementById('btnRun').disabled = false;
  log(allPass?'ALL TESTS PASSED ✔':'SOME TESTS FAILED — review report ✘', allPass?'ok':'err');
}

function stopTest(){
  if(!testActive) return;
  testActive=false;
  document.getElementById('btnRun').disabled=false;
  const pill=document.getElementById('testPill');
  pill.className='sb-pill'; pill.textContent='STOPPED';
  setLED(2,'off');
  log('Test aborted by user — LED2 OFF','warn');
}

// Start polling on load
startPolling();
log('Live polling active at '+POLL_MS+'ms intervals (relative URL mode — AP+STA)', 'info');
</script>
</body>
</html>
)rawliteral";

#endif // INDEX_H
