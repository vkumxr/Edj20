<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>EDJ20 | Wimera Systems — Test Dashboard</title>
<link href="https://fonts.googleapis.com/css2?family=IBM+Plex+Mono:wght@400;500&family=Inter:wght@300;400;500;600&display=swap" rel="stylesheet">
<style>
  :root {
    --green:      #2e7d32;
    --green-mid:  #388e3c;
    --green-lt:   #e8f5e9;
    --green-bar:  #43a047;
    --green-hi:   #1b5e20;
    --red:        #c62828;
    --red-lt:     #ffebee;
    --amber:      #f57f17;
    --amber-lt:   #fff8e1;
    --blue:       #1565c0;
    --white:      #ffffff;
    --bg:         #f7f8fa;
    --border:     #e0e4ea;
    --text:       #1a1f2e;
    --text-mid:   #4a5568;
    --text-dim:   #9aa5b4;
    --mono:       'IBM Plex Mono', monospace;
    --sans:       'Inter', sans-serif;
  }
  *, *::before, *::after { margin:0; padding:0; box-sizing:border-box; }
  body { font-family:var(--sans); background:var(--bg); color:var(--text); min-height:100vh; font-size:13px; }

  /* ══ HEADER ══ */
  header {
    background:var(--white);
    border-bottom: 2px solid var(--green);
    height: 68px;
    display: flex; align-items: center; justify-content: space-between;
    padding: 0 32px;
  }
  .logo-block { display:flex; align-items:center; gap:14px; }
  .brand-text { display:flex; flex-direction:column; gap:1px; }
  .brand-name { font-size:17px; font-weight:600; color:var(--green-hi); letter-spacing:0.5px; }
  .brand-sub  { font-size:11px; color:var(--text-dim); font-weight:400; letter-spacing:0.3px; }

  .header-center { display:flex; flex-direction:column; align-items:center; gap:2px; }
  .device-id   { font-family:var(--mono); font-size:20px; font-weight:500; color:var(--text); letter-spacing:5px; }
  .device-tag  { font-size:11px; color:var(--text-dim); letter-spacing:1px; }

  .header-right { display:flex; align-items:center; gap:24px; }
  .conn-pill {
    display:flex; align-items:center; gap:7px;
    background:var(--green-lt); border:1px solid #c8e6c9;
    padding:5px 12px; border-radius:20px;
    font-size:11px; color:var(--green-hi); font-weight:500; letter-spacing:0.5px;
  }
  .conn-dot { width:7px; height:7px; border-radius:50%; background:var(--green-mid); }
  .conn-dot.off { background:var(--red); }
  .sys-time { font-family:var(--mono); font-size:15px; color:var(--text-mid); letter-spacing:2px; }

  /* ══ INFO STRIP ══ */
  .info-strip {
    background:var(--white);
    border-bottom:1px solid var(--border);
    padding:0 32px;
    height:36px;
    display:flex; align-items:center; gap:0;
  }
  .si {
    display:flex; align-items:center; gap:6px;
    padding:0 20px 0 0; margin-right:20px;
    border-right:1px solid var(--border);
    font-size:11px; color:var(--text-dim);
  }
  .si:last-of-type { border-right:none; }
  .si .v { font-family:var(--mono); color:var(--text-mid); font-size:11px; }
  .test-badge {
    margin-left:auto;
    padding:3px 12px; border-radius:3px;
    font-family:var(--mono); font-size:10px; font-weight:500; letter-spacing:1px;
    background:var(--bg); color:var(--text-dim); border:1px solid var(--border);
  }
  .test-badge.running { background:var(--green-lt); color:var(--green); border-color:#c8e6c9; animation:pulse .9s ease infinite; }
  .test-badge.complete{ background:var(--green-lt); color:var(--green-hi); border-color:#c8e6c9; }
  .test-badge.error   { background:var(--red-lt);   color:var(--red);     border-color:#ffcdd2; }
  @keyframes pulse { 0%,100%{opacity:1} 50%{opacity:.5} }

  /* ══ LAYOUT ══ */
  .layout {
    display:grid;
    grid-template-columns:280px 1fr 272px;
    min-height:calc(100vh - 138px);
    gap:0;
  }

  /* ══ SIDEBAR ══ */
  .sidebar {
    background:var(--white);
    border-right:1px solid var(--border);
    padding:28px 20px;
    display:flex; flex-direction:column; gap:28px;
    overflow-y:auto;
  }
  .sidebar.right { border-right:none; border-left:1px solid var(--border); }

  .sec-label {
    font-size:10px; font-weight:600; letter-spacing:2px; text-transform:uppercase;
    color:var(--text-dim); margin-bottom:0;
  }

  .section { display:flex; flex-direction:column; gap:10px; }

  /* ── DI channels ── */
  .ch-grid { display:grid; grid-template-columns:1fr 1fr; gap:8px; }
  .ch-box {
    background:var(--bg); border:1px solid var(--border); border-radius:6px;
    padding:12px 12px 10px; display:flex; flex-direction:column; gap:6px;
    transition:all .2s;
  }
  .ch-box.hi { background:var(--green-lt); border-color:#a5d6a7; }
  .ch-lbl { font-size:10px; color:var(--text-dim); font-weight:500; letter-spacing:0.5px; }
  .ch-val { font-family:var(--mono); font-size:14px; color:var(--text-dim); font-weight:500; }
  .ch-val.hi { color:var(--green-mid); }
  .ch-bar { height:3px; background:var(--border); border-radius:2px; overflow:hidden; }
  .ch-bar-fill { height:100%; width:0%; background:var(--green-bar); transition:width .3s; border-radius:2px; }

  /* ── DO buttons ── */
  .do-item {
    display:flex; align-items:center; justify-content:space-between;
    padding:10px 0; border-bottom:1px solid var(--bg);
  }
  .do-item:last-child { border-bottom:none; }
  .do-lbl { font-family:var(--mono); font-size:12px; color:var(--text-mid); }
  .do-btns { display:flex; gap:6px; }
  .tbtn {
    padding:5px 14px; border-radius:4px;
    border:1px solid var(--border); background:var(--bg);
    font-size:11px; font-weight:500; cursor:pointer;
    color:var(--text-dim); transition:all .15s;
  }
  .tbtn.on.active, .tbtn.on:hover  { background:var(--green-lt); border-color:#a5d6a7; color:var(--green-hi); }
  .tbtn.off.active,.tbtn.off:hover { background:var(--red-lt);   border-color:#ffcdd2; color:var(--red); }

  /* ── Analog meter ── */
  .meter-item {
    display:flex; align-items:center; gap:10px;
    padding:8px 0; border-bottom:1px solid var(--bg);
  }
  .meter-item:last-child { border-bottom:none; }
  .meter-name { font-family:var(--mono); font-size:10px; color:var(--text-dim); width:28px; flex-shrink:0; }
  .meter-track { flex:1; height:6px; background:var(--border); border-radius:3px; overflow:hidden; }
  .meter-fill  { height:100%; background:var(--green-bar); border-radius:3px; transition:width .4s; }
  .meter-val   { font-family:var(--mono); font-size:12px; color:var(--green-mid); width:48px; text-align:right; }

  /* ── LED ── */
  .led-item {
    display:flex; align-items:center; justify-content:space-between;
    padding:9px 0; border-bottom:1px solid var(--bg);
  }
  .led-item:last-child { border-bottom:none; }
  .led-lbl { display:flex; align-items:center; gap:9px; font-family:var(--mono); font-size:11px; color:var(--text-mid); }
  .led-dot {
    width:11px; height:11px; border-radius:50%;
    background:#e0e4ea; border:1.5px solid var(--border); transition:all .3s;
  }
  .led-dot.on-green { background:#43a047; border-color:#388e3c; }
  .led-dot.on-blue  { background:#1976d2; border-color:#1565c0; }
  .led-dot.blink    { animation:ledblink .6s ease infinite; }
  @keyframes ledblink { 0%,100%{opacity:1} 50%{opacity:.1} }
  .led-ctrls { display:flex; gap:4px; }
  .lbtn {
    padding:3px 9px; border:1px solid var(--border); background:var(--bg);
    color:var(--text-dim); font-size:10px; cursor:pointer;
    border-radius:4px; transition:all .15s;
  }
  .lbtn:hover { border-color:var(--green-mid); color:var(--green-mid); background:var(--green-lt); }

  /* ── Modbus stats ── */
  .mb-row {
    display:flex; justify-content:space-between; align-items:center;
    padding:6px 0; border-bottom:1px solid var(--bg);
  }
  .mb-row:last-child { border-bottom:none; }
  .mb-k { font-size:10px; color:var(--text-dim); font-weight:500; letter-spacing:0.5px; text-transform:uppercase; }
  .mb-v { font-family:var(--mono); font-size:11px; color:var(--text-mid); }

  /* ══ CENTER ══ */
  .center {
    background:var(--bg);
    padding:28px 24px;
    display:flex; flex-direction:column; gap:20px;
    overflow-y:auto;
  }

  /* ── Test banner ── */
  .test-banner {
    background:var(--white); border:1px solid var(--border);
    border-radius:8px; padding:20px 24px;
    display:flex; align-items:center; gap:20px;
  }
  .tb-stage { min-width:200px; }
  .tb-stage-label {
    font-family:var(--mono); font-size:13px; font-weight:500;
    color:var(--text); letter-spacing:2px;
  }
  .tb-stage-desc { font-size:11px; color:var(--text-dim); margin-top:4px; line-height:1.5; }
  .tb-progress { flex:1; }
  .tb-prog-hdr {
    display:flex; justify-content:space-between;
    font-size:11px; color:var(--text-dim); margin-bottom:8px; font-weight:500;
  }
  .tb-track { height:5px; background:var(--border); border-radius:3px; overflow:hidden; }
  .tb-fill {
    height:100%; width:0%;
    background:linear-gradient(90deg, var(--green-mid), var(--green-bar));
    border-radius:3px; transition:width .5s ease;
  }
  .tb-btns { display:flex; gap:10px; flex-shrink:0; }
  .btn-run {
    padding:10px 24px; background:var(--green-mid); color:#fff;
    border:none; border-radius:5px; font-size:13px; font-weight:600;
    cursor:pointer; transition:background .15s; letter-spacing:0.5px;
  }
  .btn-run:hover { background:var(--green-hi); }
  .btn-run:disabled { opacity:.35; cursor:not-allowed; }
  .btn-stop {
    padding:10px 18px; background:var(--white); color:var(--red);
    border:1px solid #ffcdd2; border-radius:5px;
    font-size:13px; font-weight:600; cursor:pointer; transition:all .15s;
  }
  .btn-stop:hover { background:var(--red-lt); }

  /* ── Module grid ── */
  .module-grid { display:grid; grid-template-columns:repeat(3,1fr); gap:12px; }
  .mod-card {
    background:var(--white); border:1px solid var(--border);
    border-top:3px solid var(--border);
    border-radius:8px; padding:16px;
    display:flex; flex-direction:column; gap:10px;
    transition:border-color .25s, border-top-color .25s;
  }
  .mod-card.active { border-top-color:var(--green-mid); border-color:#c8e6c9; }
  .mod-card.pass   { border-top-color:var(--green-mid); }
  .mod-card.fail   { border-top-color:var(--red); }

  .mod-hdr { display:flex; align-items:center; justify-content:space-between; }
  .mod-name { font-size:13px; font-weight:600; color:var(--text); letter-spacing:0.3px; }
  .badge {
    padding:2px 8px; border-radius:4px;
    font-size:10px; font-weight:600; letter-spacing:0.5px;
  }
  .b-pend { background:var(--bg);      color:var(--text-dim); border:1px solid var(--border); }
  .b-act  { background:var(--green-lt);color:var(--green-mid);border:1px solid #c8e6c9; animation:pulse .9s ease infinite; }
  .b-pass { background:var(--green-lt);color:var(--green-hi); border:1px solid #a5d6a7; }
  .b-fail { background:var(--red-lt);  color:var(--red);      border:1px solid #ffcdd2; }

  .mod-chips { display:flex; flex-wrap:wrap; gap:5px; }
  .chip {
    padding:2px 8px; border-radius:4px;
    background:var(--bg); border:1px solid var(--border);
    font-family:var(--mono); font-size:9px; color:var(--text-dim); font-weight:500;
    transition:all .2s;
  }
  .chip.ok      { background:var(--green-lt); border-color:#a5d6a7; color:var(--green-hi); }
  .chip.err     { background:var(--red-lt);   border-color:#ffcdd2; color:var(--red); }
  .chip.testing { background:var(--green-lt); border-color:#c8e6c9; color:var(--green-mid); animation:pulse .7s ease infinite; }
  .mod-msg { font-size:11px; color:var(--text-dim); min-height:16px; line-height:1.5; }

  /* ── Event log ── */
  .log-panel { background:var(--white); border:1px solid var(--border); border-radius:8px; overflow:hidden; }
  .log-hdr {
    padding:10px 16px; border-bottom:1px solid var(--border);
    display:flex; align-items:center; justify-content:space-between;
    background:var(--bg);
  }
  .log-title { font-size:11px; font-weight:600; color:var(--text-mid); letter-spacing:1px; text-transform:uppercase; }
  .log-clr {
    font-size:11px; color:var(--text-dim); background:var(--white);
    border:1px solid var(--border); padding:3px 10px; cursor:pointer;
    border-radius:4px; transition:all .15s;
  }
  .log-clr:hover { border-color:var(--green-mid); color:var(--green-mid); }
  .log-body {
    height:148px; overflow-y:auto; padding:10px 16px;
    font-family:var(--mono); font-size:10px; line-height:2;
  }
  .log-body::-webkit-scrollbar { width:3px; }
  .log-body::-webkit-scrollbar-thumb { background:var(--border); border-radius:2px; }
  .log-entry { display:flex; gap:12px; }
  .log-ts { color:var(--text-dim); flex-shrink:0; }
  .log-m.info { color:var(--text-mid); }
  .log-m.ok   { color:var(--green-mid); }
  .log-m.err  { color:var(--red); }
  .log-m.warn { color:var(--amber); }
  .log-m.cmd  { color:var(--blue); }

  /* ── Report table ── */
  .rpt-tbl { width:100%; border-collapse:collapse; }
  .rpt-tbl th {
    font-size:10px; font-weight:600; color:var(--text-dim); letter-spacing:1px;
    text-transform:uppercase; text-align:left; padding:6px 10px;
    border-bottom:1px solid var(--border);
  }
  .rpt-tbl td {
    font-size:11px; color:var(--text-mid); padding:7px 10px;
    border-bottom:1px solid var(--bg);
  }
  .rpt-tbl tr:last-child td { border-bottom:none; }
  .r-pass { color:var(--green-mid); font-weight:600; }
  .r-fail { color:var(--red);       font-weight:600; }
  .r-pend { color:var(--text-dim); }

  /* ══ FOOTER ══ */
  footer {
    background:var(--white); border-top:1px solid var(--border);
    padding:10px 32px;
    display:flex; align-items:center; justify-content:space-between;
    font-size:11px; color:var(--text-dim);
  }
  .ft-items { display:flex; gap:28px; }
  .ft-it { display:flex; gap:6px; }
  .ft-it .k { color:var(--text-dim); }
  .ft-it .v { font-family:var(--mono); color:var(--text-mid); }
</style>
</head>
<body>

<!-- HEADER -->
<header>
  <div class="logo-block">
    <!-- Wimera logo: green W-pulse waveform on white -->
    <svg width="44" height="44" viewBox="0 0 44 44" fill="none" xmlns="http://www.w3.org/2000/svg">
      <rect width="44" height="44" rx="6" fill="#e8f5e9"/>
      <polyline points="5,14 12,30 19,20 26,30 33,14" stroke="#2e7d32" stroke-width="2.8" stroke-linecap="round" stroke-linejoin="round" fill="none"/>
      <circle cx="5"  cy="14" r="2" fill="#2e7d32"/>
      <circle cx="12" cy="30" r="2" fill="#43a047"/>
      <circle cx="19" cy="20" r="2" fill="#43a047"/>
      <circle cx="26" cy="30" r="2" fill="#43a047"/>
      <circle cx="33" cy="14" r="2" fill="#2e7d32"/>
      <line x1="4" y1="37" x2="40" y2="37" stroke="#a5d6a7" stroke-width="1"/>
    </svg>
    <div class="brand-text">
      <span class="brand-name">Wimera Systems</span>
      <span class="brand-sub">Industrial IoT Solutions</span>
    </div>
  </div>

  <div class="header-center">
    <div class="device-id">EDJ20</div>
    <div class="device-tag">IIoT Edge Device &mdash; Test Dashboard</div>
  </div>

  <div class="header-right">
    <div class="conn-pill">
      <div class="conn-dot" id="connDot"></div>
      <span id="connLabel">AP+STA</span>
    </div>
    <div class="sys-time" id="sysTime">--:--:--</div>
  </div>
</header>

<!-- INFO STRIP -->
<div class="info-strip">
  <div class="si">Device <span class="v">EDJ20-001</span></div>
  <div class="si">FW <span class="v">1.0.0</span></div>
  <div class="si">SoC <span class="v">ESP32-S3</span></div>
  <div class="si">ESP-IDF <span class="v">v5.1.2</span></div>
  <div class="si">Mode <span class="v">AP+STA</span></div>
  <div class="si">IP <span class="v" id="devIP">---</span></div>
  <div class="test-badge" id="testPill">IDLE</div>
</div>

<!-- LAYOUT -->
<div class="layout">

  <!-- LEFT SIDEBAR -->
  <div class="sidebar">

    <div class="section">
      <div class="sec-label">Digital Inputs</div>
      <div class="ch-grid">
        <div class="ch-box" id="diBox_1"><div class="ch-lbl">DI 1</div><div class="ch-val" id="diVal_1">LOW</div><div class="ch-bar"><div class="ch-bar-fill" id="diBar_1"></div></div></div>
        <div class="ch-box" id="diBox_2"><div class="ch-lbl">DI 2</div><div class="ch-val" id="diVal_2">LOW</div><div class="ch-bar"><div class="ch-bar-fill" id="diBar_2"></div></div></div>
        <div class="ch-box" id="diBox_3"><div class="ch-lbl">DI 3</div><div class="ch-val" id="diVal_3">LOW</div><div class="ch-bar"><div class="ch-bar-fill" id="diBar_3"></div></div></div>
        <div class="ch-box" id="diBox_4"><div class="ch-lbl">DI 4</div><div class="ch-val" id="diVal_4">LOW</div><div class="ch-bar"><div class="ch-bar-fill" id="diBar_4"></div></div></div>
      </div>
    </div>

    <div class="section">
      <div class="sec-label">Digital Outputs</div>
      <div class="do-item">
        <span class="do-lbl">DO 1</span>
        <div class="do-btns">
          <button class="tbtn on"         id="do1On"  onclick="setDO(1,1)">ON</button>
          <button class="tbtn off active"  id="do1Off" onclick="setDO(1,0)">OFF</button>
        </div>
      </div>
      <div class="do-item">
        <span class="do-lbl">DO 2</span>
        <div class="do-btns">
          <button class="tbtn on"         id="do2On"  onclick="setDO(2,1)">ON</button>
          <button class="tbtn off active"  id="do2Off" onclick="setDO(2,0)">OFF</button>
        </div>
      </div>
    </div>

    <div class="section">
      <div class="sec-label">Analog Inputs</div>
      <div class="meter-item">
        <div class="meter-name">AI 1</div>
        <div class="meter-track"><div class="meter-fill" id="aiFill_1" style="width:0%"></div></div>
        <div class="meter-val" id="aiVal_1">0.00 V</div>
      </div>
      <div class="meter-item">
        <div class="meter-name">AI 2</div>
        <div class="meter-track"><div class="meter-fill" id="aiFill_2" style="width:0%"></div></div>
        <div class="meter-val" id="aiVal_2">0.00 V</div>
      </div>
    </div>

  </div>

  <!-- CENTER -->
  <div class="center">

    <!-- Test banner -->
    <div class="test-banner">
      <div class="tb-stage">
        <div class="tb-stage-label" id="stageLabel">READY TO TEST</div>
        <div class="tb-stage-desc" id="stageDesc">All interfaces idle. Press Run Test to begin.</div>
      </div>
      <div class="tb-progress">
        <div class="tb-prog-hdr">
          <span>Progress</span>
          <span id="progPct">0%</span>
        </div>
        <div class="tb-track">
          <div class="tb-fill" id="progBar"></div>
        </div>
      </div>
      <div class="tb-btns">
        <button class="btn-run"  id="btnRun" onclick="startTest()">&#9654; Run Test</button>
        <button class="btn-stop" onclick="stopTest()">&#9632; Stop</button>
      </div>
    </div>

    <!-- Module cards -->
    <div class="module-grid">

      <div class="mod-card" id="mod_di">
        <div class="mod-hdr"><span class="mod-name">Digital In</span><span class="badge b-pend" id="badge_di">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_di_1">DI1</span>
          <span class="chip" id="chip_di_2">DI2</span>
          <span class="chip" id="chip_di_3">DI3</span>
          <span class="chip" id="chip_di_4">DI4</span>
        </div>
        <div class="mod-msg" id="msg_di">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_do">
        <div class="mod-hdr"><span class="mod-name">Digital Out</span><span class="badge b-pend" id="badge_do">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_do_1">DO1</span>
          <span class="chip" id="chip_do_2">DO2</span>
        </div>
        <div class="mod-msg" id="msg_do">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_ai">
        <div class="mod-hdr"><span class="mod-name">Analog In</span><span class="badge b-pend" id="badge_ai">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_ai_1">AI1</span>
          <span class="chip" id="chip_ai_2">AI2</span>
        </div>
        <div class="mod-msg" id="msg_ai">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_mb">
        <div class="mod-hdr"><span class="mod-name">Modbus RTU</span><span class="badge b-pend" id="badge_mb">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_mb_ap">A+</span>
          <span class="chip" id="chip_mb_bn">B−</span>
        </div>
        <div class="mod-msg" id="msg_mb">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_ct">
        <div class="mod-hdr"><span class="mod-name">CT Sensors</span><span class="badge b-pend" id="badge_ct">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_ct_1">CT1</span>
          <span class="chip" id="chip_ct_2">CT2</span>
          <span class="chip" id="chip_ct_3">CT3</span>
        </div>
        <div class="mod-msg" id="msg_ct">Awaiting test start...</div>
      </div>

      <div class="mod-card" id="mod_led">
        <div class="mod-hdr"><span class="mod-name">LED Control</span><span class="badge b-pend" id="badge_led">PENDING</span></div>
        <div class="mod-chips">
          <span class="chip" id="chip_led_2">LED2</span>
          <span class="chip" id="chip_led_3">LED3</span>
        </div>
        <div class="mod-msg" id="msg_led">Awaiting test start...</div>
      </div>

    </div>

    <!-- Event log -->
    <div class="log-panel">
      <div class="log-hdr">
        <span class="log-title">Event Log</span>
        <button class="log-clr" onclick="clearLog()">Clear</button>
      </div>
      <div class="log-body" id="logBody">
        <div class="log-entry"><span class="log-ts" id="initTs"></span><span class="log-m info">System initialised. Awaiting test sequence.</span></div>
      </div>
    </div>

  </div>

  <!-- RIGHT SIDEBAR -->
  <div class="sidebar right">

    <div class="section">
      <div class="sec-label">LED Control</div>
      <div class="led-item">
        <div class="led-lbl"><div class="led-dot on-green" id="led1Dot"></div>LED 1</div>
        <span style="font-size:10px;color:var(--text-dim);">POWER</span>
      </div>
      <div class="led-item">
        <div class="led-lbl"><div class="led-dot" id="led2Dot"></div>LED 2</div>
        <div class="led-ctrls">
          <button class="lbtn" onclick="setLED(2,'on')">ON</button>
          <button class="lbtn" onclick="setLED(2,'off')">OFF</button>
          <button class="lbtn" onclick="setLED(2,'blink')">BLK</button>
        </div>
      </div>
      <div class="led-item">
        <div class="led-lbl"><div class="led-dot" id="led3Dot"></div>LED 3</div>
        <div class="led-ctrls">
          <button class="lbtn" onclick="setLED(3,'on')">ON</button>
          <button class="lbtn" onclick="setLED(3,'off')">OFF</button>
          <button class="lbtn" onclick="setLED(3,'blink')">BLK</button>
        </div>
      </div>
    </div>

    <div class="section">
      <div class="sec-label">Modbus RTU</div>
      <div class="mb-row"><span class="mb-k">Lines</span><span class="mb-v">A+ / B−</span></div>
      <div class="mb-row"><span class="mb-k">Protocol</span><span class="mb-v">RTU</span></div>
      <div class="mb-row"><span class="mb-k">Baud</span><span class="mb-v" id="mbBaud">9600</span></div>
      <div class="mb-row"><span class="mb-k">Last TX</span><span class="mb-v" id="mbLastTx">—</span></div>
      <div class="mb-row"><span class="mb-k">Last RX</span><span class="mb-v" id="mbLastRx">—</span></div>
      <div class="mb-row"><span class="mb-k">Status</span><span class="mb-v" id="mbStatus">IDLE</span></div>
    </div>

    <div class="section">
      <div class="sec-label">CT Sensors</div>
      <div class="meter-item">
        <div class="meter-name">CT 1</div>
        <div class="meter-track"><div class="meter-fill" id="ctFill_1" style="width:0%"></div></div>
        <div class="meter-val" id="ctVal_1">0.0 A</div>
      </div>
      <div class="meter-item">
        <div class="meter-name">CT 2</div>
        <div class="meter-track"><div class="meter-fill" id="ctFill_2" style="width:0%"></div></div>
        <div class="meter-val" id="ctVal_2">0.0 A</div>
      </div>
      <div class="meter-item">
        <div class="meter-name">CT 3</div>
        <div class="meter-track"><div class="meter-fill" id="ctFill_3" style="width:0%"></div></div>
        <div class="meter-val" id="ctVal_3">0.0 A</div>
      </div>
    </div>

    <div class="section">
      <div class="sec-label">Test Report</div>
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

  </div>

</div>

<!-- FOOTER -->
<footer>
  <div class="ft-items">
    <div class="ft-it"><span class="k">Device</span><span class="v">EDJ20-001</span></div>
    <div class="ft-it"><span class="k">SoC</span><span class="v">ESP32-S3</span></div>
    <div class="ft-it"><span class="k">ESP-IDF</span><span class="v">v5.1.2</span></div>
    <div class="ft-it"><span class="k">Mode</span><span class="v">AP+STA</span></div>
  </div>
  <span>&copy; 2025 Wimera Systems Pvt. Ltd.</span>
</footer>

<script>
// AP+STA: all fetch() use relative paths — see original design notes
const POLL_MS = 500;
let pollTimer = null, testActive = false;

const STEPS = [
  { key:'di',  label:'TESTING DI',    desc:'Verifying 24V digital input states on DI1–DI4...' },
  { key:'do',  label:'TESTING DO',    desc:'Toggling DO1 & DO2, verifying output states...' },
  { key:'ai',  label:'TESTING AI',    desc:'Reading ADC on AI1 & AI2, checking 0–3.3V range...' },
  { key:'mb',  label:'TESTING MODBUS',desc:'Sending RTU frame via A+/B−, awaiting slave response...' },
  { key:'ct',  label:'TESTING CT',    desc:'Sampling AC current from CT1, CT2, CT3...' },
  { key:'led', label:'TESTING LEDs',  desc:'Cycling LED2 & LED3 through ON / BLINK / OFF...' },
];
const CHIP_MAP = {
  di:['di_1','di_2','di_3','di_4'], do:['do_1','do_2'],
  ai:['ai_1','ai_2'], mb:['mb_ap','mb_bn'],
  ct:['ct_1','ct_2','ct_3'], led:['led_2','led_3'],
};

function tickClock(){
  const n=new Date();
  document.getElementById('sysTime').textContent=
    String(n.getHours()).padStart(2,'0')+':'+
    String(n.getMinutes()).padStart(2,'0')+':'+
    String(n.getSeconds()).padStart(2,'0');
}
document.getElementById('initTs').textContent=new Date().toLocaleTimeString();
setInterval(tickClock,1000); tickClock();

function log(msg,cls='info'){
  const b=document.getElementById('logBody');
  const d=document.createElement('div'); d.className='log-entry';
  d.innerHTML=`<span class="log-ts">${new Date().toLocaleTimeString()}</span><span class="log-m ${cls}">${msg}</span>`;
  b.appendChild(d); b.scrollTop=b.scrollHeight;
}
function clearLog(){ document.getElementById('logBody').innerHTML=''; }

function startPolling(){ if(!pollTimer) pollTimer=setInterval(poll,POLL_MS); }
function stopPolling(){  if(pollTimer){ clearInterval(pollTimer); pollTimer=null; } }

async function poll(){
  try { const r=await fetch('/api/di'); if(r.ok){ const d=await r.json();
    for(let i=1;i<=4;i++){ const v=d['DI'+i];
      document.getElementById('diBox_'+i).classList.toggle('hi',!!v);
      const el=document.getElementById('diVal_'+i);
      el.textContent=v?'HIGH':'LOW'; el.className='ch-val'+(v?' hi':'');
      document.getElementById('diBar_'+i).style.width=v?'100%':'0%';
    }}} catch(e){}
  try { const r=await fetch('/api/ai'); if(r.ok){ const d=await r.json();
    for(let i=1;i<=2;i++){ const v=parseFloat(d['AI'+i]||0);
      document.getElementById('aiFill_'+i).style.width=Math.min(100,(v/3.3)*100).toFixed(1)+'%';
      document.getElementById('aiVal_'+i).textContent=v.toFixed(2)+' V';
    }}} catch(e){}
  try { const r=await fetch('/api/ct'); if(r.ok){ const d=await r.json();
    for(let i=1;i<=3;i++){ const v=parseFloat(d['CT'+i]||0);
      document.getElementById('ctFill_'+i).style.width=Math.min(100,(v/20)*100).toFixed(1)+'%';
      document.getElementById('ctVal_'+i).textContent=v.toFixed(1)+' A';
    }}} catch(e){}
}

async function setDO(ch,val){
  try { const r=await fetch(`/api/do?ch=${ch}&val=${val}`);
    if(r.ok){
      document.getElementById(`do${ch}On`).classList.toggle('active',!!val);
      document.getElementById(`do${ch}Off`).classList.toggle('active',!val);
      log(`DO${ch} → ${val?'ON':'OFF'}`,'cmd');
    }} catch(e){ log(`DO${ch} command failed`,'err'); }
}
async function setLED(num,state){
  try { const r=await fetch(`/api/led?num=${num}&state=${state}`);
    if(r.ok){
      const dot=document.getElementById(`led${num}Dot`);
      dot.classList.remove('on-green','on-blue','blink');
      if(state==='on')    dot.classList.add('on-blue');
      if(state==='blink') dot.classList.add('on-blue','blink');
      log(`LED${num} → ${state.toUpperCase()}`,'cmd');
    }} catch(e){ log(`LED${num} command failed`,'err'); }
}

function setBadge(k,c,t){ const e=document.getElementById('badge_'+k); e.className='badge '+c; e.textContent=t; }
function setCard(k,c){ document.getElementById('mod_'+k).className='mod-card '+c; }
function setChip(id,c){ const e=document.getElementById('chip_'+id); if(e) e.className='chip '+c; }
function setMsg(k,t){ document.getElementById('msg_'+k).textContent=t; }
function setReport(k,pass){
  const e=document.getElementById('rpt_'+k);
  e.textContent=pass===null?'—':(pass?'PASS':'FAIL');
  e.className=pass===null?'r-pend':(pass?'r-pass':'r-fail');
}
function setProgress(step){
  const pct=Math.round((step/STEPS.length)*100);
  document.getElementById('progBar').style.width=pct+'%';
  document.getElementById('progPct').textContent=pct+'%';
  if(step<STEPS.length){
    document.getElementById('stageLabel').textContent=STEPS[step].label;
    document.getElementById('stageDesc').textContent=STEPS[step].desc;
  } else {
    document.getElementById('stageLabel').textContent='TEST COMPLETE';
    document.getElementById('stageDesc').textContent='All interfaces tested. See report.';
  }
}

async function runStep(i){
  const s=STEPS[i];
  setBadge(s.key,'b-act','TESTING'); setCard(s.key,'active');
  CHIP_MAP[s.key].forEach(id=>setChip('chip_'+id,'testing'));
  log('▶ '+s.label,'cmd');
  let pass=false;
  try {
    const r=await fetch(`/api/test/${s.key}`,{method:'POST'});
    if(r.ok){ const d=await r.json(); pass=d.pass===true;
      setMsg(s.key,d.message||(pass?'All channels OK':'One or more channels failed'));
      if(d.channels) Object.entries(d.channels).forEach(([ch,ok])=>setChip('chip_'+s.key+'_'+ch.toLowerCase().replace(/[^a-z0-9]/g,''),ok?'ok':'err'));
      else CHIP_MAP[s.key].forEach(id=>setChip('chip_'+id,pass?'ok':'err'));
    } else { setMsg(s.key,'HTTP '+r.status); CHIP_MAP[s.key].forEach(id=>setChip('chip_'+id,'err')); }
  } catch(e){ setMsg(s.key,'Request failed: '+e.message); CHIP_MAP[s.key].forEach(id=>setChip('chip_'+id,'err')); }
  setBadge(s.key,pass?'b-pass':'b-fail',pass?'PASS':'FAIL');
  setCard(s.key,pass?'pass':'fail');
  setReport(s.key,pass);
  log((pass?'✔':'✘')+' '+s.label+' → '+(pass?'PASS':'FAIL'),pass?'ok':'err');
  return pass;
}

async function startTest(){
  if(testActive) return; testActive=true;
  document.getElementById('btnRun').disabled=true;
  const pill=document.getElementById('testPill');
  pill.className='test-badge running'; pill.textContent='RUNNING';
  STEPS.forEach(s=>{
    setBadge(s.key,'b-pend','PENDING'); setCard(s.key,'');
    setReport(s.key,null); setMsg(s.key,'Queued...');
    CHIP_MAP[s.key].forEach(id=>setChip('chip_'+id,''));
  });
  document.getElementById('progBar').style.width='0%';
  document.getElementById('progPct').textContent='0%';
  await setLED(2,'on'); log('Test sequence started — LED2 ON','info');
  let allPass=true;
  for(let i=0;i<STEPS.length;i++){
    if(!testActive) break; setProgress(i);
    const ok=await runStep(i); if(!ok) allPass=false;
    await new Promise(r=>setTimeout(r,350));
  }
  setProgress(STEPS.length);
  await setLED(2,'off'); log('Test sequence complete — LED2 OFF','info');
  pill.className=allPass?'test-badge complete':'test-badge error';
  pill.textContent=allPass?'PASS':'FAIL';
  testActive=false; document.getElementById('btnRun').disabled=false;
  log(allPass?'ALL TESTS PASSED ✔':'SOME TESTS FAILED — review report ✘',allPass?'ok':'err');
}
function stopTest(){
  if(!testActive) return; testActive=false;
  document.getElementById('btnRun').disabled=false;
  const pill=document.getElementById('testPill');
  pill.className='test-badge'; pill.textContent='STOPPED';
  setLED(2,'off'); log('Test aborted by user — LED2 OFF','warn');
}

startPolling();
log('Live polling active at '+POLL_MS+'ms intervals (AP+STA mode)','info');
</script>
</body>
</html>
