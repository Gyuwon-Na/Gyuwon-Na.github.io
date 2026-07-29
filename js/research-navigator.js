(() => {
  const nav = document.querySelector('.clifford-jump-nav');
  const container = nav?.querySelector('.container');
  const sections = Array.from(
    document.querySelectorAll('.clifford-detail-content > .detail-section[id]')
  );

  if (!nav || !container || sections.length < 2) return;

  const existingLabels = new Map(
    Array.from(container.querySelectorAll('a[href^="#"]')).map((link) => [
      link.getAttribute('href').slice(1),
      link.textContent.trim()
    ])
  );

  const getLabel = (section) => {
    const explicitLabel = existingLabels.get(section.id);
    if (explicitLabel) return explicitLabel;

    const kicker = section.querySelector('.clifford-section-kicker')?.textContent.trim();
    if (kicker) return kicker;

    return section.id
      .split('-')
      .map((word) => word.charAt(0).toUpperCase() + word.slice(1))
      .join(' ');
  };

  const heading = document.createElement('span');
  heading.className = 'research-navigator__heading';
  heading.textContent = 'On this page';

  const progressTrack = document.createElement('span');
  progressTrack.className = 'research-navigator__progress';
  progressTrack.setAttribute('aria-hidden', 'true');

  const progressValue = document.createElement('span');
  progressValue.className = 'research-navigator__progress-value';
  progressTrack.append(progressValue);

  const fragment = document.createDocumentFragment();
  const links = sections.map((section, index) => {
    const link = document.createElement('a');
    const label = getLabel(section);

    link.href = `#${section.id}`;
    link.title = label;
    link.innerHTML = `
      <span class="research-navigator__marker" aria-hidden="true">${String(index + 1).padStart(2, '0')}</span>
      <span class="research-navigator__label">${label}</span>
    `;
    fragment.append(link);
    return link;
  });

  container.replaceChildren(heading, fragment);
  nav.prepend(progressTrack);
  nav.classList.add('research-navigator');

  let activeIndex = -1;
  let ticking = false;
  const prefersReducedMotion = window.matchMedia('(prefers-reduced-motion: reduce)');

  const setActive = (nextIndex) => {
    if (nextIndex === activeIndex) return;
    activeIndex = nextIndex;

    links.forEach((link, index) => {
      const isActive = index === activeIndex;
      link.classList.toggle('is-active', isActive);
      if (isActive) {
        link.setAttribute('aria-current', 'location');
      } else {
        link.removeAttribute('aria-current');
      }
    });

    if (window.innerWidth < 1500) {
      const activeLink = links[activeIndex];
      const targetLeft = activeLink.offsetLeft - (container.clientWidth - activeLink.offsetWidth) / 2;
      container.scrollTo({
        left: Math.max(0, targetLeft),
        behavior: prefersReducedMotion.matches ? 'auto' : 'smooth'
      });
    }
  };

  const updateNavigator = () => {
    const readingLine = window.innerHeight * 0.34;
    let nextIndex = 0;

    sections.forEach((section, index) => {
      if (section.getBoundingClientRect().top <= readingLine) nextIndex = index;
    });

    setActive(nextIndex);

    const firstTop = sections[0].getBoundingClientRect().top + window.scrollY;
    const lastSection = sections.at(-1);
    const lastBottom = lastSection.getBoundingClientRect().bottom + window.scrollY;
    const range = Math.max(1, lastBottom - firstTop - window.innerHeight * 0.4);
    const progress = Math.min(1, Math.max(0, (window.scrollY + readingLine - firstTop) / range));
    progressValue.style.setProperty('--research-progress', `${progress * 100}%`);

    ticking = false;
  };

  const requestUpdate = () => {
    if (ticking) return;
    ticking = true;
    window.requestAnimationFrame(updateNavigator);
  };

  links.forEach((link) => {
    link.addEventListener('click', () => {
      const targetIndex = links.indexOf(link);
      setActive(targetIndex);
    });
  });

  container.addEventListener('keydown', (event) => {
    const focusedIndex = links.indexOf(document.activeElement);
    if (focusedIndex < 0) return;

    const keyTargets = {
      ArrowDown: Math.min(links.length - 1, focusedIndex + 1),
      ArrowRight: Math.min(links.length - 1, focusedIndex + 1),
      ArrowUp: Math.max(0, focusedIndex - 1),
      ArrowLeft: Math.max(0, focusedIndex - 1),
      Home: 0,
      End: links.length - 1
    };

    const targetIndex = keyTargets[event.key];
    if (targetIndex === undefined) return;

    event.preventDefault();
    links[targetIndex].focus();
  });

  window.addEventListener('scroll', requestUpdate, { passive: true });
  window.addEventListener('resize', requestUpdate);
  window.addEventListener('load', requestUpdate, { once: true });
  updateNavigator();
})();
