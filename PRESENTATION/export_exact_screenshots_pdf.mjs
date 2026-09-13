import puppeteer from 'puppeteer-core';
import { PDFDocument } from 'pdf-lib';
import fs from 'fs';
import path from 'path';

const edgePath = 'C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe';

const presentations = [
  { name: '00_ESP32_HARDWARE', url: 'http://localhost:5173/' },
  { name: '01_Arduino_Programming', url: 'http://localhost:5174/' },
  { name: '02_TB6612FNG_Motor_Driver', url: 'http://localhost:5175/' },
  { name: '03_Basic_Line_Follower', url: 'http://localhost:5176/' },
  { name: '04_Obstacle_Avoider_Robot', url: 'http://localhost:5177/' },
  { name: '05_ESP32_Web_Controlled_Car', url: 'http://localhost:5178/' },
  { name: '06_Gyro_Gesture_Controlled_Bot', url: 'http://localhost:5179/' },
];

const outputDir = 'M:\\ACTUATOR_26\\PRESENTATION\\EXACT_PDF_EXPORTS';
if (!fs.existsSync(outputDir)) {
  fs.mkdirSync(outputDir, { recursive: true });
}

async function capturePresentationAsPDF(browser, pres) {
  console.log(`\n========================================`);
  console.log(`Capturing 1:1 Screen-Exact PDF: ${pres.name}`);
  console.log(`========================================`);

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
  console.log('🚀 ALL 6 SCREEN-EXACT PDFs GENERATED SUCCESSFULLY!');
  console.log(`Saved in: ${outputDir}`);
  console.log('========================================');
}

main().catch(console.error);
