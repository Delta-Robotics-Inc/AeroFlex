import assert from "node:assert/strict";
import { readFile } from "node:fs/promises";

const dashboard = await readFile(new URL("../index.html", import.meta.url), "utf8");
const scriptMatch = dashboard.match(/<script>([\s\S]*?)<\/script>/);
assert.ok(scriptMatch, "dashboard must contain one inline application script");
new Function(scriptMatch[1]);

for (const id of [
  "connectBtn",
  "demoBtn",
  "armBtn",
  "manualModeBtn",
  "manualSpeed",
  "manualSpeedValue",
  "stopBtn",
  "leadForm",
  "trend",
  "log",
]) {
  assert.match(dashboard, new RegExp(`id="${id}"`), `missing #${id}`);
}

assert.match(dashboard, /data-hold="U"/, "missing manual Up hold control");
assert.match(dashboard, /data-hold="D"/, "missing manual Down hold control");
assert.match(dashboard, /send\(`j\$\{button\.dataset\.hold\},\$\{\$\("manualSpeed"\)\.value\}\\n`\)/, "hold control must send variable-rate manual command");
assert.match(dashboard, /function stopManualHold\(\)/, "hold release must send Stop");

const workerModule = await import(
  `${new URL("./dist/server/index.js", import.meta.url).href}?test=${Date.now()}`
);
const worker = workerModule.default;

const root = await worker.fetch(new Request("https://rig.example/"));
assert.equal(root.status, 200);
assert.match(root.headers.get("content-type"), /text\/html/);
assert.equal(root.headers.get("permissions-policy"), "serial=(self)");
const rootHtml = await root.text();
assert.match(rootHtml, /AEROFLEX \/\/ TEST-RIG/);
assert.match(
  rootHtml,
  /<meta property="og:image" content="https:\/\/rig\.example\/og\.png">/,
);

const image = await worker.fetch(new Request("https://rig.example/og.png"));
assert.equal(image.status, 200);
assert.equal(image.headers.get("content-type"), "image/png");
assert.ok((await image.arrayBuffer()).byteLength > 1_000_000);

const missing = await worker.fetch(new Request("https://rig.example/missing"));
assert.equal(missing.status, 404);

const longestCoreFrame =
  "@T v=1 ms=4294967295 mot=down_slow dir=down pps=1600 sent=2147483647 req=2147483647 pv=1 posp=-2147483648 posmm=-12345.678 enc=-2147483648 inv=4294967295 top=1 bot=1 safe=1 bref=1 tref=1\n";
assert.ok(
  Buffer.byteLength(longestCoreFrame) < 256,
  "core frame must fit the Uno R4 USB transmit buffer",
);

console.log("Dashboard, worker, social card, and telemetry-size checks passed.");
