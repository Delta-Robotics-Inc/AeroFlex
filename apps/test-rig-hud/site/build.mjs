import { mkdir, readFile, rm, writeFile } from "node:fs/promises";
import { dirname, resolve } from "node:path";
import { fileURLToPath } from "node:url";

const here = dirname(fileURLToPath(import.meta.url));
const dashboardPath = resolve(here, "..", "index.html");
const socialCardPath = resolve(here, "..", "og.png");
const outputDirectory = resolve(here, "dist", "server");
const outputPath = resolve(outputDirectory, "index.js");

const dashboard = await readFile(dashboardPath, "utf8");
const socialCard = (await readFile(socialCardPath)).toString("base64");

const worker = `
const dashboard = ${JSON.stringify(dashboard)};
const socialCardBase64 = ${JSON.stringify(socialCard)};
let socialCardBytes;

function decodeSocialCard() {
  if (socialCardBytes) return socialCardBytes;
  const binary = atob(socialCardBase64);
  socialCardBytes = Uint8Array.from(binary, character => character.charCodeAt(0));
  return socialCardBytes;
}

export default {
  async fetch(request) {
    const url = new URL(request.url);
    if (url.pathname === "/" || url.pathname === "/index.html" || url.pathname === "/console.html") {
      const absoluteCard = new URL("/og.png", url.origin).toString();
      const html = dashboard.replace(
        '<meta property="og:image" content="/og.png">',
        '<meta property="og:image" content="' + absoluteCard + '">'
      );
      return new Response(request.method === "HEAD" ? null : html, {
        headers: {
          "Content-Type": "text/html; charset=utf-8",
          "Cache-Control": "no-cache",
          "Permissions-Policy": "serial=(self)",
          "X-Content-Type-Options": "nosniff",
          "Referrer-Policy": "no-referrer"
        }
      });
    }
    if (url.pathname === "/og.png") {
      return new Response(request.method === "HEAD" ? null : decodeSocialCard(), {
        headers: {
          "Content-Type": "image/png",
          "Cache-Control": "public, max-age=86400, immutable",
          "X-Content-Type-Options": "nosniff"
        }
      });
    }
    return new Response("Not found", { status: 404 });
  }
};
`;

await rm(resolve(here, "dist"), { recursive: true, force: true });
await mkdir(outputDirectory, { recursive: true });
await writeFile(outputPath, worker, "utf8");
console.log(`Built ${outputPath}`);
