(() => {
  const slugify = (value) => value
    .toLowerCase()
    .replace(/&/g, ' and ')
    .replace(/[^a-z0-9]+/g, '-')
    .replace(/^-+|-+$/g, '') || 'section';

  const ensureProjectNavigator = () => {
    const content = document.querySelector('.detail-content:not(.clifford-detail-content)');
    if (!content || document.querySelector('.project-jump-nav, .clifford-jump-nav')) return;

    const nav = document.createElement('nav');
    nav.className = 'project-jump-nav';
    nav.setAttribute('aria-label', 'Page sections');
    nav.dataset.navigatorContent = '.detail-content';
    nav.innerHTML = '<div class="container"></div>';
    content.before(nav);
  };

  const configureReturnLink = () => {
    const main = document.querySelector('#main-content');
    const topBackLink = main?.querySelector('.detail-hero .back-btn');
    if (!topBackLink) return;

    const path = window.location.pathname.toLowerCase();
    const projectCategory = [
      ['autonomous_driving', 'autonomous', 'Autonomous Systems'],
      ['graphics', 'graphics', 'Computer Graphics'],
      ['computer_vision', 'vision', 'Computer Vision'],
      ['games', 'game', 'Games']
    ].find(([directory]) => path.includes(`/portfolio/${directory}/`));

    let href = '';
    let label = '';

    if (projectCategory) {
      href = `../../pages/Projects.html#${projectCategory[1]}`;
      label = `Back to ${projectCategory[2]}`;
    } else if (path.includes('/portfolio/research/')) {
      const isFeatured = path.includes('cliffordtransformer.html');
      href = `../../pages/Research.html#${isFeatured ? 'featured-research' : 'additional-research'}`;
      label = `Back to ${isFeatured ? 'Featured Research' : 'Additional Research'}`;
    }

    if (!href) return;

    const icon = topBackLink.querySelector('[data-lucide="arrow-left"]');
    topBackLink.href = href;
    topBackLink.replaceChildren();
    if (icon) topBackLink.append(icon);
    topBackLink.append(` ${label}`);
  };

  const addReturnLink = () => {
    const main = document.querySelector('#main-content');
    const topBackLink = main?.querySelector('.detail-hero .back-btn');
    const content = main?.querySelector('.detail-content');
    if (!topBackLink || !content || content.querySelector('.detail-return')) return;

    const returnContainer = document.createElement('div');
    returnContainer.className = 'detail-return';

    const returnLink = topBackLink.cloneNode(true);
    returnLink.classList.add('detail-return__link');
    returnContainer.append(returnLink);
    content.append(returnContainer);
  };

  const initializeNavigator = (nav) => {
    const container = nav.querySelector('.container');
    const contentSelector = nav.dataset.navigatorContent || '.clifford-detail-content, .detail-content';
    const content = document.querySelector(contentSelector);
    if (!container || !content) return;

    const usedIds = new Set(Array.from(document.querySelectorAll('[id]')).map((element) => element.id));
    const sectionEntries = Array.from(content.children)
      .filter((element) => element.classList.contains('detail-section'))
      .map((section) => {
        const previousElement = section.previousElementSibling;
        const previousTitle = previousElement?.classList.contains('detail-section-title')
          ? previousElement
          : null;
        const title = previousTitle || section.querySelector('.detail-section-title');
        const target = previousTitle || section;

        if (!target.id) {
          const baseId = slugify(title?.textContent.trim() || 'section');
          let candidateId = baseId;
          let suffix = 2;
          while (usedIds.has(candidateId)) {
            candidateId = `${baseId}-${suffix}`;
            suffix += 1;
          }
          target.id = candidateId;
          usedIds.add(candidateId);
        }

        return { section, target, title };
      });

    if (sectionEntries.length < 2) return;

    const existingLabels = new Map(
      Array.from(container.querySelectorAll('a[href^="#"]')).map((link) => [
        link.getAttribute('href').slice(1),
        link.textContent.trim()
      ])
    );

    const getLabel = ({ target, title }) => {
      const explicitLabel = existingLabels.get(target.id);
      if (explicitLabel) return explicitLabel;

      const kicker = target.querySelector('.clifford-section-kicker')?.textContent.trim();
      if (kicker) return kicker;

      return title?.textContent.trim() || target.id
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
    const links = sectionEntries.map((entry, index) => {
      const link = document.createElement('a');
      const label = getLabel(entry);

      link.href = `#${entry.target.id}`;
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

      sectionEntries.forEach(({ target }, index) => {
        if (target.getBoundingClientRect().top <= readingLine) nextIndex = index;
      });

      setActive(nextIndex);

      const firstTop = sectionEntries[0].target.getBoundingClientRect().top + window.scrollY;
      const lastTarget = sectionEntries.at(-1).section;
      const lastBottom = lastTarget.getBoundingClientRect().bottom + window.scrollY;
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
        setActive(links.indexOf(link));
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
  };

  ensureProjectNavigator();
  configureReturnLink();
  addReturnLink();
  document
    .querySelectorAll('.clifford-jump-nav, .project-jump-nav')
    .forEach(initializeNavigator);
})();
