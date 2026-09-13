import Reveal from 'reveal.js';
import 'reveal.js/reveal.css';
import 'reveal.js/theme/black.css';
import './style.css';

const deck = new Reveal({
  hash: true,
  controls: true,
  progress: true,
  slideNumber: 'c/t',
  center: false,
  transition: 'fade',
  backgroundTransition: 'fade'
});

deck.initialize();
