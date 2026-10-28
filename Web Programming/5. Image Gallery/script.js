/**
 * ==============================================================================
 * MONOLITH // Interactive Image Gallery & Slideshow Engine
 * ==============================================================================
 * Vanilla JavaScript implementation prioritizing:
 * 1. Clean algorithmic state management (modulo arithmetic for cycling)
 * 2. Predictable lifecycle (clean event bindings, interval teardown)
 * 3. High educational readability for lab evaluations / viva explanations
 * ==============================================================================
 */

document.addEventListener('DOMContentLoaded', function () {
    'use strict';

    // ---------------------------------------------------------------------------
    // 1. Exhibition Dataset
    // ---------------------------------------------------------------------------
    // Each object represents an artwork containing high-res source, local SVG fallback,
    // category tagging, and architectural metadata.
    const galleryData = [
        {
            id: 1,
            code: 'ARC-01',
            title: 'Pavilion Alpha Cantilever',
            category: 'brutalism',
            year: '2024',
            location: 'Berlin, Germany',
            // High-resolution Unsplash photo with local SVG fallback
            src: 'https://images.unsplash.com/photo-1600585154340-be6161a56a0c?auto=format&fit=crop&w=1200&q=80',
            fallback: 'images/img-01.svg',
            caption: 'Sharp geometric concrete massing suspended over a raw stone plaza under diffused light.'
        },
        {
            id: 2,
            code: 'ARC-02',
            title: 'Rotunda Light Aperture',
            category: 'interiors',
            year: '2023',
            location: 'Kyoto, Japan',
            src: 'https://images.unsplash.com/photo-1513694203232-719a280e022f?auto=format&fit=crop&w=1200&q=80',
            fallback: 'images/img-02.svg',
            caption: 'Monolithic interior light well casting deep parabolic shadows on untreated timber and stone.'
        },
        {
            id: 3,
            code: 'ARC-03',
            title: 'Fluted Precast Tower',
            category: 'brutalism',
            year: '2022',
            location: 'London, UK',
            src: 'https://images.unsplash.com/photo-1486406146926-c627a92ad1ab?auto=format&fit=crop&w=1200&q=80',
            fallback: 'images/img-03.svg',
            caption: 'Vertical modular ribbed concrete facade demonstrating rhythmic brutalist construction.'
        },
        {
            id: 4,
            code: 'ARC-04',
            title: 'Helicoidal Core Stair',
            category: 'interiors',
            year: '2024',
            location: 'Basel, Switzerland',
            src: 'https://images.unsplash.com/photo-1494526585095-c41746248156?auto=format&fit=crop&w=1200&q=80',
            fallback: 'images/img-04.svg',
            caption: 'Continuous cast-in-place spiral staircase connecting four subterranean archival galleries.'
        },
        {
            id: 5,
            code: 'ARC-05',
            title: 'Anodized Louver Facade',
            category: 'minimalism',
            year: '2023',
            location: 'Oslo, Norway',
            src: 'https://images.unsplash.com/photo-1506157786151-b8491531f063?auto=format&fit=crop&w=1200&q=80',
            fallback: 'images/img-05.svg',
            caption: 'Repetitive vertical aluminum louvers regulating solar intake with strict minimalist discipline.'
        },
        {
            id: 6,
            code: 'ARC-06',
            title: 'Spatial Atrium Void',
            category: 'minimalism',
            year: '2024',
            location: 'Zurich, Switzerland',
            src: 'https://images.unsplash.com/photo-1518780664697-55e3ad937233?auto=format&fit=crop&w=1200&q=80',
            fallback: 'images/img-06.svg',
            caption: 'Double-height negative space framing architectural scale, clean sightlines, and shadow geometry.'
        },
        {
            id: 7,
            code: 'ARC-07',
            title: 'Tempered Glass Pavilion',
            category: 'minimalism',
            year: '2023',
            location: 'Milan, Italy',
            src: 'https://images.unsplash.com/photo-1512917774080-9991f1c4c750?auto=format&fit=crop&w=1200&q=80',
            fallback: 'images/img-07.svg',
            caption: 'Seamless curtain wall offering pure transparency between exterior landscape and interior exhibit.'
        },
        {
            id: 8,
            code: 'ARC-08',
            title: 'Isometric Structural Cube',
            category: 'brutalism',
            year: '2024',
            location: 'Tokyo, Japan',
            src: 'https://images.unsplash.com/photo-1448630360428-65456885c650?auto=format&fit=crop&w=1200&q=80',
            fallback: 'images/img-08.svg',
            caption: 'Exposed reinforced concrete skeleton showcasing expressive structural engineering.'
        }
    ];

    // ---------------------------------------------------------------------------
    // 2. Application State Model
    // ---------------------------------------------------------------------------
    const state = {
        activeItems: [...galleryData], // Currently filtered array of items
        currentIndex: 0,               // Active index inside activeItems
        isModalOpen: false,            // Slideshow visibility flag
        isAutoPlaying: false,          // Auto-play state flag
        autoPlayTimerId: null,         // Holds setInterval ID for slide changes
        progressTimerId: null,         // Holds setInterval ID for smooth progress bar
        slideDuration: 4000,           // Duration per slide in milliseconds (4.0s)
        progressElapsed: 0,            // Elapsed time for active slide (ms)
        progressInterval: 40           // Progress bar refresh cadence (ms)
    };

    // ---------------------------------------------------------------------------
    // 3. DOM Element References
    // ---------------------------------------------------------------------------
    const galleryGrid = document.getElementById('galleryGrid');
    const galleryCounter = document.getElementById('galleryCounter');
    const filterButtons = document.querySelectorAll('.filter-btn');
    const startSlideshowBtn = document.getElementById('startSlideshowBtn');

    // Modal & Stage Elements
    const modal = document.getElementById('slideshowModal');
    const closeModalBtn = document.getElementById('closeModalBtn');
    const prevBtn = document.getElementById('prevBtn');
    const nextBtn = document.getElementById('nextBtn');
    const modalImage = document.getElementById('modalImage');
    const slideCounter = document.getElementById('slideCounter');
    const modalTag = document.getElementById('modalTag');
    const modalTitleTop = document.getElementById('modalTitleTop');
    const modalCaptionTitle = document.getElementById('modalCaptionTitle');
    const modalCaptionDescription = document.getElementById('modalCaptionDescription');
    const modalLocation = document.getElementById('modalLocation');
    const modalYear = document.getElementById('modalYear');
    const thumbnailStrip = document.getElementById('thumbnailStrip');

    // Auto-Play Controls
    const autoPlayToggleBtn = document.getElementById('autoPlayToggleBtn');
    const autoPlayIcon = document.getElementById('autoPlayIcon');
    const autoPlayLabel = document.getElementById('autoPlayLabel');
    const autoplayProgress = document.getElementById('autoplayProgress');

    // ---------------------------------------------------------------------------
    // 4. Grid Rendering & Category Filtering
    // ---------------------------------------------------------------------------

    /**
     * Renders gallery cards into the CSS Grid container based on current dataset.
     */
    function renderGalleryGrid() {
        galleryGrid.innerHTML = '';

        state.activeItems.forEach(function (item, index) {
            const card = document.createElement('article');
            card.className = 'gallery-card';
            card.setAttribute('tabindex', '0');
            card.setAttribute('role', 'button');
            card.setAttribute('aria-label', `View ${item.title} in slideshow`);

            // Build card inner HTML
            card.innerHTML = `
                <div class="card-media">
                    <img 
                        src="${item.src}" 
                        data-fallback="${item.fallback}"
                        alt="${item.title}" 
                        class="card-img" 
                        loading="lazy" 
                        onerror="this.onerror=null; this.src=this.dataset.fallback;" 
                    />
                    <span class="card-badge">${item.category.toUpperCase()}</span>
                </div>
                <div class="card-body">
                    <span class="card-index">${item.code} // ${item.year}</span>
                    <h3 class="card-title">${item.title}</h3>
                    <div class="card-meta-line">
                        <span>${item.location}</span>
                        <span>[CLICK TO EXPAND]</span>
                    </div>
                </div>
            `;

            // Clicking card opens slideshow at this specific item
            card.addEventListener('click', function () {
                openSlideshow(index);
            });

            // Keyboard accessibility (Enter or Space triggers click)
            card.addEventListener('keydown', function (e) {
                if (e.key === 'Enter' || e.key === ' ') {
                    e.preventDefault();
                    openSlideshow(index);
                }
            });

            galleryGrid.appendChild(card);
        });

        // Update counter label
        galleryCounter.textContent = `SHOWING ${state.activeItems.length} OF ${galleryData.length} WORKS`;
    }

    /**
     * Filters gallery items by category and re-renders grid.
     */
    function filterGallery(category) {
        if (category === 'all') {
            state.activeItems = [...galleryData];
        } else {
            state.activeItems = galleryData.filter(function (item) {
                return item.category.toLowerCase() === category.toLowerCase();
            });
        }

        renderGalleryGrid();
    }

    // Bind Filter Button Click Events
    filterButtons.forEach(function (button) {
        button.addEventListener('click', function () {
            filterButtons.forEach(btn => btn.classList.remove('active'));
            this.classList.add('active');

            const selectedFilter = this.getAttribute('data-filter');
            filterGallery(selectedFilter);
        });
    });

    // ---------------------------------------------------------------------------
    // 5. Slideshow Lifecycle & Navigation
    // ---------------------------------------------------------------------------

    /**
     * Opens the modal slideshow at a specific index.
     * @param {number} targetIndex - Index within state.activeItems
     */
    function openSlideshow(targetIndex = 0) {
        if (state.activeItems.length === 0) return;

        state.isModalOpen = true;
        modal.classList.add('active');
        modal.setAttribute('aria-hidden', 'false');
        document.body.classList.add('modal-open');

        // Build thumbnail strip for quick jumping
        renderThumbnails();

        // Display targeted slide
        showSlide(targetIndex);
    }

    /**
     * Closes the slideshow modal and stops auto-play.
     */
    function closeSlideshow() {
        state.isModalOpen = false;
        modal.classList.remove('active');
        modal.setAttribute('aria-hidden', 'true');
        document.body.classList.remove('modal-open');

        // Stop auto-play immediately when exiting
        stopAutoPlay();
    }

    /**
     * Updates the slide stage with the item at index.
     * Uses modulo arithmetic to safely cycle forward and backward.
     * @param {number} index
     */
    function showSlide(index) {
        const total = state.activeItems.length;
        if (total === 0) return;

        // Circular modulo wrap-around:
        // (index % total + total) % total guarantees a valid non-negative index
        state.currentIndex = ((index % total) + total) % total;
        const currentItem = state.activeItems[state.currentIndex];

        // Update typography & metadata immediately for instant responsiveness
        modalTag.textContent = `${currentItem.code} // ${currentItem.category.toUpperCase()}`;
        modalTitleTop.textContent = currentItem.title;
        modalCaptionTitle.textContent = currentItem.title;
        modalCaptionDescription.textContent = currentItem.caption;
        modalLocation.textContent = currentItem.location.toUpperCase();
        modalYear.textContent = `YEAR: ${currentItem.year}`;

        // Update counter (formatted with leading zero: e.g. "02 / 08")
        const currentFormatted = String(state.currentIndex + 1).padStart(2, '0');
        const totalFormatted = String(total).padStart(2, '0');
        slideCounter.textContent = `${currentFormatted} / ${totalFormatted}`;

        // Subtle quick cross-fade for the visual transition
        modalImage.classList.add('changing');
        modalImage.src = currentItem.src;
        modalImage.dataset.fallback = currentItem.fallback;
        modalImage.onerror = function () {
            this.onerror = null;
            this.src = this.dataset.fallback;
        };
        modalImage.alt = currentItem.title;

        setTimeout(function () {
            modalImage.classList.remove('changing');
        }, 120);

        // Synchronize active thumbnail indicator
        updateActiveThumbnail();

        // Reset auto-play progress bar on slide change
        resetProgress();
    }

    /**
     * Advances to next slide.
     */
    function nextSlide() {
        showSlide(state.currentIndex + 1);
    }

    /**
     * Navigates to previous slide.
     */
    function prevSlide() {
        showSlide(state.currentIndex - 1);
    }

    // ---------------------------------------------------------------------------
    // 6. Thumbnails Filmstrip
    // ---------------------------------------------------------------------------

    /**
     * Generates thumbnail buttons inside the modal bottom bar.
     */
    function renderThumbnails() {
        thumbnailStrip.innerHTML = '';

        state.activeItems.forEach(function (item, index) {
            const thumb = document.createElement('button');
            thumb.className = 'thumb-item';
            thumb.setAttribute('aria-label', `Jump to slide ${index + 1}: ${item.title}`);

            thumb.innerHTML = `
                <img 
                    src="${item.src}" 
                    data-fallback="${item.fallback}" 
                    alt="${item.title}" 
                    onerror="this.onerror=null; this.src=this.dataset.fallback;" 
                />
            `;

            thumb.addEventListener('click', function () {
                showSlide(index);
                if (state.isAutoPlaying) {
                    resetAutoPlay();
                }
            });

            thumbnailStrip.appendChild(thumb);
        });

        updateActiveThumbnail();
    }

    /**
     * Sets the '.active' CSS class on the current thumbnail item.
     */
    function updateActiveThumbnail() {
        const thumbs = thumbnailStrip.querySelectorAll('.thumb-item');
        thumbs.forEach(function (thumb, index) {
            if (index === state.currentIndex) {
                thumb.classList.add('active');
                // Scroll thumbnail into view smoothly
                thumb.scrollIntoView({ behavior: 'smooth', inline: 'center', block: 'nearest' });
            } else {
                thumb.classList.remove('active');
            }
        });
    }

    // ---------------------------------------------------------------------------
    // 7. Auto-Play Slideshow Engine
    // ---------------------------------------------------------------------------

    /**
     * Starts auto-play mode: sets interval timer and progresses smoothly.
     */
    function startAutoPlay() {
        state.isAutoPlaying = true;
        autoPlayToggleBtn.classList.add('active');
        autoPlayIcon.textContent = '❚❚';
        autoPlayLabel.textContent = 'AUTO-PLAY: ON';

        resetProgress();

        // Smooth progress timer (ticks every 40ms)
        state.progressTimerId = setInterval(function () {
            state.progressElapsed += state.progressInterval;
            const percentage = Math.min((state.progressElapsed / state.slideDuration) * 100, 100);
            autoplayProgress.style.width = percentage + '%';

            // Once duration has elapsed, advance to next slide
            if (state.progressElapsed >= state.slideDuration) {
                nextSlide();
            }
        }, state.progressInterval);
    }

    /**
     * Stops/pauses auto-play mode and cleans up timers.
     */
    function stopAutoPlay() {
        state.isAutoPlaying = false;
        autoPlayToggleBtn.classList.remove('active');
        autoPlayIcon.textContent = '▶';
        autoPlayLabel.textContent = 'AUTO-PLAY: OFF';

        if (state.progressTimerId) {
            clearInterval(state.progressTimerId);
            state.progressTimerId = null;
        }

        resetProgress();
    }

    /**
     * Toggles between play and pause states.
     */
    function toggleAutoPlay() {
        if (state.isAutoPlaying) {
            stopAutoPlay();
        } else {
            startAutoPlay();
        }
    }

    /**
     * Resets progress bar and counter for current slide.
     */
    function resetProgress() {
        state.progressElapsed = 0;
        autoplayProgress.style.width = '0%';
    }

    /**
     * Resets auto-play cycle after manual user interaction.
     */
    function resetAutoPlay() {
        if (state.isAutoPlaying) {
            resetProgress();
        }
    }

    // ---------------------------------------------------------------------------
    // 8. Event Listeners & Keyboard Accessibility
    // ---------------------------------------------------------------------------

    // Next / Prev button clicks
    nextBtn.addEventListener('click', function () {
        nextSlide();
        resetAutoPlay();
    });

    prevBtn.addEventListener('click', function () {
        prevSlide();
        resetAutoPlay();
    });

    // Auto-play button toggle
    autoPlayToggleBtn.addEventListener('click', toggleAutoPlay);

    // Close button click
    closeModalBtn.addEventListener('click', closeSlideshow);

    // Header "Start Slideshow" button opens modal at current first item
    startSlideshowBtn.addEventListener('click', function () {
        openSlideshow(0);
    });

    // Close modal when clicking on the dark backdrop outside slide frame
    modal.addEventListener('click', function (event) {
        if (event.target === modal || event.target.classList.contains('modal-stage')) {
            closeSlideshow();
        }
    });

    // Keyboard shortcuts (Navigation, Escape, Spacebar)
    window.addEventListener('keydown', function (event) {
        // If slideshow modal is not open, do not trap keys
        if (!state.isModalOpen) return;

        switch (event.key) {
            case 'ArrowRight':
                event.preventDefault();
                nextSlide();
                resetAutoPlay();
                break;

            case 'ArrowLeft':
                event.preventDefault();
                prevSlide();
                resetAutoPlay();
                break;

            case 'Escape':
                event.preventDefault();
                closeSlideshow();
                break;

            case ' ':
                // Spacebar toggles auto-play
                event.preventDefault();
                toggleAutoPlay();
                break;
        }
    });

    // ---------------------------------------------------------------------------
    // 9. Initial Application Bootstrap
    // ---------------------------------------------------------------------------
    renderGalleryGrid();
});
