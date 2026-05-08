document.addEventListener('DOMContentLoaded', () => {
  // Category Filter Functionality
  const filterButtons = document.querySelectorAll('.filter-btn');
  const projectSections = document.querySelectorAll('.project-category');
  const projectsOverview = document.getElementById('projects-overview');
  const overviewFilterLinks = document.querySelectorAll('.overview-filter-link');

  // Function to show/hide categories based on filter
  const filterProjects = (category) => {
    if (projectsOverview) {
      if (category === 'all') {
        projectsOverview.classList.remove('hidden');
        projectsOverview.style.display = 'block';
      } else {
        projectsOverview.classList.add('hidden');
        projectsOverview.style.display = 'none';
      }
    }

    projectSections.forEach(section => {
      const sectionCategory = section.getAttribute('data-category');
      
      if (category === 'all') {
        // All Projects uses compact overview mode.
        section.classList.add('hidden');
        section.style.display = 'none';
      } else {
        // Show only matching category
        if (sectionCategory === category) {
          section.classList.remove('hidden');
          section.style.display = 'block';
        } else {
          section.classList.add('hidden');
          section.style.display = 'none';
        }
      }
    });

    // Smooth scroll to first visible section
    setTimeout(() => {
      const firstVisibleSection = document.querySelector('.project-category:not(.hidden)');
      if (firstVisibleSection && category !== 'all') {
        firstVisibleSection.scrollIntoView({ 
          behavior: 'smooth', 
          block: 'start'
        });
      }
    }, 100);
  };

  // Add click event listeners to filter buttons
  filterButtons.forEach(button => {
    button.addEventListener('click', () => {
      // Remove active class from all buttons
      filterButtons.forEach(btn => {
        btn.classList.remove('active');
        btn.setAttribute('aria-selected', 'false');
      });

      // Add active class to clicked button
      button.classList.add('active');
      button.setAttribute('aria-selected', 'true');

      // Get category and filter
      const category = button.getAttribute('data-category');
      filterProjects(category);

      // Keep Projects landing lightweight: every fresh visit starts from the compact overview.
    });
  });

  overviewFilterLinks.forEach(link => {
    link.addEventListener('click', () => {
      const targetCategory = link.getAttribute('data-target-category');
      const targetButton = document.querySelector(`.filter-btn[data-category="${targetCategory}"]`);

      if (targetButton) {
        targetButton.click();
      }
    });
  });

  // Initialize with compact overview.
  const savedFilterButton = document.querySelector('[data-category="all"]');
  
  if (savedFilterButton) {
    savedFilterButton.click();
  } else {
    filterProjects('all');
  }

  // Keyboard navigation for filters
  filterButtons.forEach((button, index) => {
    button.addEventListener('keydown', (e) => {
      let targetIndex;

      switch(e.key) {
        case 'ArrowRight':
          targetIndex = (index + 1) % filterButtons.length;
          filterButtons[targetIndex].focus();
          filterButtons[targetIndex].click();
          e.preventDefault();
          break;
        
        case 'ArrowLeft':
          targetIndex = (index - 1 + filterButtons.length) % filterButtons.length;
          filterButtons[targetIndex].focus();
          filterButtons[targetIndex].click();
          e.preventDefault();
          break;
        
        case 'Home':
          filterButtons[0].focus();
          filterButtons[0].click();
          e.preventDefault();
          break;
        
        case 'End':
          filterButtons[filterButtons.length - 1].focus();
          filterButtons[filterButtons.length - 1].click();
          e.preventDefault();
          break;
      }
    });
  });

  // Scroll reveal animation for project cards
  const observerOptions = {
    threshold: 0.1,
    rootMargin: '0px 0px -50px 0px'
  };

  const observer = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        entry.target.style.opacity = '1';
        entry.target.style.transform = 'translateY(0)';
      }
    });
  }, observerOptions);

  // Observe all project cards
  const projectCards = document.querySelectorAll('.project-detail-card');
  projectCards.forEach(card => {
    observer.observe(card);
  });

  // Smooth scroll for anchor links
  document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
      const targetId = this.getAttribute('href');
      if (targetId !== '#') {
        e.preventDefault();
        const targetElement = document.querySelector(targetId);
        if (targetElement) {
          targetElement.scrollIntoView({
            behavior: 'smooth',
            block: 'start'
          });
        }
      }
    });
  });

  // Add loading state to external links
  const externalLinks = document.querySelectorAll('a[target="_blank"]');
  externalLinks.forEach(link => {
    link.addEventListener('click', function() {
      // Optional: Add loading animation or feedback
      this.style.opacity = '0.6';
      setTimeout(() => {
        this.style.opacity = '1';
      }, 300);
    });
  });

  // Dynamic project count display
  const updateProjectCount = () => {
    const visibleSections = document.querySelectorAll('.project-category:not(.hidden)');
    let totalProjects = 0;

    if (projectsOverview && !projectsOverview.classList.contains('hidden')) {
      totalProjects = projectsOverview.querySelectorAll('.compact-project-card').length;
    } else {
      visibleSections.forEach(section => {
        const cards = section.querySelectorAll('.project-detail-card');
        totalProjects += cards.length;
      });
    }

    // You can display this count somewhere if needed
    console.log(`Showing ${totalProjects} project(s)`);
  };

  // Update count on filter change
  filterButtons.forEach(button => {
    button.addEventListener('click', () => {
      setTimeout(updateProjectCount, 100);
    });
  });

  // Initial count
  updateProjectCount();

  // Handle browser back/forward buttons
  window.addEventListener('popstate', () => {
    const savedFilterButton = document.querySelector('[data-category="all"]');
    if (savedFilterButton) {
      savedFilterButton.click();
    }
  });

  // Performance optimization: Lazy load images
  const imageObserver = new IntersectionObserver((entries) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        const img = entry.target;
        if (img.dataset.src) {
          img.src = img.dataset.src;
          img.removeAttribute('data-src');
          imageObserver.unobserve(img);
        }
      }
    });
  });

  // Observe all images with data-src attribute
  document.querySelectorAll('img[data-src]').forEach(img => {
    imageObserver.observe(img);
  });
});
