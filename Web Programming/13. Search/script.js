"use strict";

const input   = document.getElementById("q");
const status  = document.getElementById("status");
const list    = document.getElementById("results");

const API = "https://en.wikipedia.org/w/api.php";
const DEBOUNCE_MS = 300;

let timer = null;        // debounce timer
let controller = null;   // AbortController for the in-flight request

function setStatus(text, isError = false) {
  status.textContent = text;
  status.classList.toggle("error", isError);
}

// Wikipedia returns snippets with <span class="searchmatch">. Rebuild them
// with DOM nodes instead of innerHTML so nothing untrusted is executed.
function buildSnippet(html) {
  const p = document.createElement("p");
  p.className = "snippet";
  const doc = new DOMParser().parseFromString(html, "text/html");
  doc.body.childNodes.forEach(node => {
    if (node.nodeType === Node.ELEMENT_NODE && node.classList.contains("searchmatch")) {
      const em = document.createElement("em");
      em.textContent = node.textContent;
      p.appendChild(em);
    } else {
      p.appendChild(document.createTextNode(node.textContent));
    }
  });
  return p;
}

function render(items) {
  list.replaceChildren();
  items.forEach((item, i) => {
    const li = document.createElement("li");
    li.style.animationDelay = `${i * 30}ms`;

    const body = document.createElement("div");

    const a = document.createElement("a");
    a.href = `https://en.wikipedia.org/wiki/${encodeURIComponent(item.title.replace(/ /g, "_"))}`;
    a.target = "_blank";
    a.rel = "noopener";
    a.textContent = item.title;

    const meta = document.createElement("span");
    meta.className = "meta";
    meta.textContent = `${item.wordcount.toLocaleString()} words`;

    body.append(a, buildSnippet(item.snippet), meta);
    li.appendChild(body);
    list.appendChild(li);
  });
}

async function search(query) {
  // Cancel any request still in flight so old responses never overwrite new ones.
  if (controller) controller.abort();
  controller = new AbortController();

  const params = new URLSearchParams({
    action: "query",
    list: "search",
    srsearch: query,
    srlimit: "8",
    format: "json",
    origin: "*"          // enables CORS for anonymous requests
  });

  setStatus("Searching…");

  try {
    const res = await fetch(`${API}?${params}`, { signal: controller.signal });
    if (!res.ok) throw new Error(`HTTP ${res.status}`);

    const data = await res.json();
    const items = data.query.search;

    if (items.length === 0) {
      list.replaceChildren();
      setStatus(`No results for “${query}”`);
      return;
    }

    render(items);
    setStatus(`${data.query.searchinfo.totalhits.toLocaleString()} results — showing ${items.length}`);
  } catch (err) {
    if (err.name === "AbortError") return;   // superseded by a newer keystroke
    list.replaceChildren();
    setStatus("Could not reach the server. Check your connection.", true);
    console.error(err);
  }
}

input.addEventListener("input", () => {
  clearTimeout(timer);
  const query = input.value.trim();

  if (query.length === 0) {
    if (controller) controller.abort();
    list.replaceChildren();
    setStatus("Waiting for input");
    return;
  }

  // Wait until the user pauses typing before hitting the API.
  timer = setTimeout(() => search(query), DEBOUNCE_MS);
});
