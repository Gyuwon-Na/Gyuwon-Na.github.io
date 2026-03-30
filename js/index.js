document.addEventListener('DOMContentLoaded', () => {
  // --- Navigation Toggle Logic ---
  const menuToggle = document.querySelector('.menu-toggle');
  const navOverlay = document.querySelector('.nav-overlay');
  const navLinks = document.querySelectorAll('.nav-link, .nav-btn');

  if (menuToggle) {
    menuToggle.addEventListener('click', () => {
      document.body.classList.toggle('nav-open');
    });
  }

  // Close navigation when clicking links
  navLinks.forEach(link => {
    link.addEventListener('click', () => {
      document.body.classList.remove('nav-open');
    });
  });
  
  // Scroll header design change
  const header = document.querySelector('.main-header');
  if (header) {
    window.addEventListener('scroll', () => {
      if (window.scrollY > 50) {
        header.classList.add('scrolled');
      } else {
        header.classList.remove('scrolled');
      }
    });
  }
  
  // --- Research Carousel with Improved Transitions ---
  const slides = document.querySelectorAll('.research-card');
  const prevBtn = document.querySelector('.nav-arrow.prev');
  const nextBtn = document.querySelector('.nav-arrow.next');
  const indicators = document.querySelectorAll('.indicator');

  if (slides.length === 0) return;

  let currentIndex = 0;
  let isTransitioning = false; // Prevent multiple rapid clicks

  // Show slide with improved transition handling
  const showSlide = (index) => {
    if (isTransitioning) return; // Prevent overlapping transitions
    
    isTransitioning = true;

    // Remove active class from all slides immediately
    slides.forEach(slide => {
      slide.classList.remove('active');
    });
    
    // Update indicators
    indicators.forEach(dot => {
      dot.classList.remove('active');
    });

    // Small delay to ensure clean transition (prevents text ghosting)
    setTimeout(() => {
      slides[index].classList.add('active');
      if(indicators[index]) indicators[index].classList.add('active');
      
      // Reset transition lock after animation completes
      setTimeout(() => {
        isTransitioning = false;
      }, 400); // Match CSS transition duration
    }, 50);
  };

  // Initialize first slide
  showSlide(0);

  // Next button
  if (nextBtn) {
    nextBtn.addEventListener('click', () => {
      if (isTransitioning) return;
      currentIndex++;
      if (currentIndex >= slides.length) {
        currentIndex = 0;
      }
      showSlide(currentIndex);
    });
  }

  // Previous button
  if (prevBtn) {
    prevBtn.addEventListener('click', () => {
      if (isTransitioning) return;
      currentIndex--;
      if (currentIndex < 0) {
        currentIndex = slides.length - 1;
      }
      showSlide(currentIndex);
    });
  }

  // Indicator click
  indicators.forEach((dot, index) => {
    dot.addEventListener('click', () => {
      if (isTransitioning || currentIndex === index) return;
      currentIndex = index;
      showSlide(currentIndex);
    });
  });

  // Optional: Keyboard navigation
  document.addEventListener('keydown', (e) => {
    if (slides.length === 0) return;
    
    if (e.key === 'ArrowLeft') {
      if (prevBtn) prevBtn.click();
    } else if (e.key === 'ArrowRight') {
      if (nextBtn) nextBtn.click();
    }
  });
});