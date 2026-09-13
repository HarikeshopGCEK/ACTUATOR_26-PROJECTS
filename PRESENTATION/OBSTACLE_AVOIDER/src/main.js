import Reveal from 'reveal.js';
import RevealHighlight from 'reveal.js/plugin/highlight';
import 'reveal.js/reveal.css';
import 'reveal.js/theme/black.css';
import 'reveal.js/plugin/highlight/monokai.css';
import './style.css';

const deck = new Reveal({
  hash: true,
  controls: true,
  progress: true,
  slideNumber: 'c/t',
  center: false,
  transition: 'slide',
  backgroundTransition: 'fade',
  plugins: [ RevealHighlight ]
});

deck.initialize();
