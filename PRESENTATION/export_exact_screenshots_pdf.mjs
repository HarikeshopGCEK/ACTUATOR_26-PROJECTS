import puppeteer from 'puppeteer-core';
import { PDFDocument } from 'pdf-lib';
import fs from 'fs';
import path from 'path';
import http from 'http';
import { spawn } from 'child_process';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const edgePath = 'C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe';
const baseDir = __dirname;

const presentations = [
  { name: '00_ESP32_HARDWARE', dir: 'ESP32_HARDWARE', port: 5173, url: 'http://localhost:5173/' },
  { name: '01_Arduino_Programming', dir: 'ARDUINO_PROGRAMMING', port: 5174, url: 'http://localhost:5174/' },
  { name: '02_TB6612FNG_Motor_Driver', dir: 'MOTOR_DRIVER', port: 5175, url: 'http://localhost:5175/' },
  { name: '03_Basic_Line_Follower', dir: 'BASIC_LINEFOLLOWER', port: 5176, url: 'http://localhost:5176/' },
  { name: '04_Obstacle_Avoider_Robot', dir: 'OBSTACLE_AVOIDER', port: 5177, url: 'http://localhost:5177/' },
  { name: '05_ESP32_Web_Controlled_Car', dir: 'WEB_CONTROLLED_CAR', port: 5178, url: 'http://localhost:5178/' },
  { name: '06_Gyro_Gesture_Controlled_Bot', dir: 'GESTURE_CONTROLLED_CAR', port: 5179, url: 'http://localhost:5179/' },
];

const outputDir = path.join(baseDir, 'EXACT_PDF_EXPORTS');
if (!fs.existsSync(outputDir)) {
  fs.mkdirSync(outputDir, { recursive: true });
}

function isServerRunning(url) {
  return new Promise((resolve) => {
    const req = http.get(url, (res) => {
      resolve(true);
    });
    req.on('error', () => resolve(false));
    req.setTimeout(1000, () => {
      req.destroy();
      resolve(false);
    });
  });
}

async function ensureServerRunning(pres) {
  const running = await isServerRunning(pres.url);
  if (running) {
    console.log(`  ℹ Server already running at ${pres.url}`);
    return null;
  }

  console.log(`  🚀 Auto-starting dev server for ${pres.name} on port ${pres.port}...`);
  const isWin = process.platform === 'win32';
  const npxCmd = isWin ? 'npx.cmd' : 'npx';
  const targetDir = path.join(baseDir, pres.dir);

  const serverProc = spawn(npxCmd, ['vite', '--port', pres.port.toString(), '--strictPort'], {
    cwd: targetDir,
    stdio: 'ignore',
    shell: true
  });

  for (let attempt = 0; attempt < 30; attempt++) {
    await new Promise(r => setTimeout(r, 500));
    if (await isServerRunning(pres.url)) {
      console.log(`  ✓ Server started successfully at ${pres.url}`);
      return serverProc;
    }
  }

  console.warn(`  ⚠️ Warning: Server at ${pres.url} did not respond within 15 seconds.`);
  return serverProc;
}

function stopServerProcess(serverProc) {
  if (!serverProc) return;
  try {
    if (process.platform === 'win32') {
      spawn('taskkill', ['/pid', serverProc.pid.toString(), '/f', '/t'], { stdio: 'ignore' });
    } else {
      serverProc.kill('SIGTERM');
    }
    console.log(`  🛑 Auto-started server stopped.`);
  } catch (e) {
    // ignore shutdown errors
  }
}

async function capturePresentationAsPDF(browser, pres) {
  console.log(`\n========================================`);
  console.log(`Capturing 1:1 Screen-Exact PDF: ${pres.name}`);
  console.log(`========================================`);

  const serverProc = await ensureServerRunning(pres);

  try {
    const page = await browser.newPage();
    await page.setViewport({ width: 1920, height: 1080, deviceScaleFactor: 2 });

    await page.goto(pres.url, { waitUntil: 'networkidle0' });
    await new Promise(r => setTimeout(r, 1500));

    const totalSlides = await page.evaluate(() => document.querySelectorAll('.slides > section').length);
    console.log(`Detected ${totalSlides} slides.`);

    const pdfDoc = await PDFDocument.create();

    for (let i = 0; i < totalSlides; i++) {
      await page.evaluate((idx) => { window.location.hash = `#/${idx}`; }, i);
      await new Promise(r => setTimeout(r, 450));

      const pngBuffer = await page.screenshot({ type: 'png', fullPage: false });
      const image = await pdfDoc.embedPng(pngBuffer);
      const pdfPage = pdfDoc.addPage([1920, 1080]);
      pdfPage.drawImage(image, { x: 0, y: 0, width: 1920, height: 1080 });

      console.log(`  ✓ Captured & Stitched Slide ${i + 1} / ${totalSlides}`);
    }

    await page.close();

    const pdfBytes = await pdfDoc.save();
    const pdfPath = path.join(outputDir, `${pres.name}.pdf`);
    fs.writeFileSync(pdfPath, pdfBytes);

    console.log(`🎉 SUCCESS! Screen-Exact PDF created: ${pdfPath}`);
  } finally {
    stopServerProcess(serverProc);
  }
}

async function main() {
  console.log('Starting Screen-Exact 1:1 PDF Export Routine...');
  const browser = await puppeteer.launch({
    executablePath: edgePath,
    headless: true,
    args: ['--no-sandbox', '--disable-setuid-sandbox', '--force-color-profile=srgb']
  });

  for (const pres of presentations) {
    try {
      await capturePresentationAsPDF(browser, pres);
    } catch (err) {
      console.error(`Error exporting ${pres.name}:`, err);
    }
  }

  await browser.close();
  console.log('\n========================================');
  console.log('🚀 ALL SCREEN-EXACT PDFs GENERATED SUCCESSFULLY!');
  console.log(`Saved in: ${outputDir}`);
  console.log('========================================');
}

main().catch(console.error);
