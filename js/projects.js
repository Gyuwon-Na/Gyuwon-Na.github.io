document.addEventListener('DOMContentLoaded', () => {
  const filterButtons = document.querySelectorAll('.filter-btn');
  const projectCategories = document.querySelectorAll('.project-category');
  const showOnlyButtons = document.querySelectorAll('.show-only-btn');

  const filterProjects = (category) => {
    projectCategories.forEach((section) => {
      const isVisible = category === 'all' || section.dataset.category === category;
      section.classList.toggle('hidden', !isVisible);
    });
  };

  filterButtons.forEach((button, index) => {
    button.addEventListener('click', () => {
      filterButtons.forEach((item) => {
        item.classList.remove('active');
        item.setAttribute('aria-selected', 'false');
      });

      button.classList.add('active');
      button.setAttribute('aria-selected', 'true');
      filterProjects(button.dataset.category);
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

  showOnlyButtons.forEach((button) => {
    button.addEventListener('click', () => {
      const targetButton = document.querySelector(`.filter-btn[data-category="${button.dataset.targetCategory}"]`);
      if (targetButton) targetButton.click();
    });
  });

  filterProjects('all');
});
