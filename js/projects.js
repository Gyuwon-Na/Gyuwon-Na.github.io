document.addEventListener('DOMContentLoaded', () => {
  const filterButtons = document.querySelectorAll('.filter-btn');
  const projectCategories = document.querySelectorAll('.project-category');
  const validCategories = new Set(Array.from(filterButtons, (button) => button.dataset.category));

  const getCategoryFromHash = () => {
    const category = window.location.hash.slice(1);
    return validCategories.has(category) ? category : 'all';
  };

  const filterProjects = (category) => {
    projectCategories.forEach((section) => {
      const isVisible = category === 'all' || section.dataset.category === category;
      section.classList.toggle('hidden', !isVisible);
    });
  };

  const activateCategory = (category) => {
    const targetCategory = validCategories.has(category) ? category : 'all';

    filterButtons.forEach((button) => {
      const isActive = button.dataset.category === targetCategory;
      button.classList.toggle('active', isActive);
      button.setAttribute('aria-selected', String(isActive));
    });

    filterProjects(targetCategory);
    return targetCategory;
  };

  const updateHash = (category) => {
    const nextUrl = category === 'all'
      ? `${window.location.pathname}${window.location.search}`
      : `#${category}`;
    window.history.replaceState(null, '', nextUrl);
  };

  const scrollToCategory = (category) => {
    const target = category === 'all'
      ? document.querySelector('.projects-list')
      : document.querySelector(`.project-category[data-category="${category}"]`);
    target?.scrollIntoView({ block: 'start' });
  };

  filterButtons.forEach((button, index) => {
    button.addEventListener('click', () => {
      const category = activateCategory(button.dataset.category);
      updateHash(category);
      scrollToCategory(category);
    });

    button.addEventListener('keydown', (event) => {
      const lastIndex = filterButtons.length - 1;
      let targetIndex = index;

      if (event.key === 'ArrowRight') targetIndex = index === lastIndex ? 0 : index + 1;
      if (event.key === 'ArrowLeft') targetIndex = index === 0 ? lastIndex : index - 1;
      if (event.key === 'Home') targetIndex = 0;
      if (event.key === 'End') targetIndex = lastIndex;
      if (targetIndex === index) return;

      event.preventDefault();
      filterButtons[targetIndex].focus();
      filterButtons[targetIndex].click();
    });
  });

  const applyHashFilter = () => {
    const category = activateCategory(getCategoryFromHash());
    if (category !== 'all') {
      window.requestAnimationFrame(() => scrollToCategory(category));
    }
  };

  window.addEventListener('hashchange', applyHashFilter);
  applyHashFilter();
});
