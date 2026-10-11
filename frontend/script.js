const $ = (id) => document.getElementById(id);
let gameState = null;
let requestInProgress = false;

async function api(path, options = {}) {
  const response = await fetch(path, {
    headers: { "Content-Type": "application/json" },
    ...options
  });
  if (!response.ok) throw new Error(`HTTP ${response.status}`);
  return response.json();
}

async function refreshState() {
  try {
    gameState = await api("/api/state");
    $("connection").textContent = "C++ game engine connected";
    $("status-dot").style.background = "var(--green)";
    render();
  } catch (error) {
    $("connection").textContent = "Game engine offline — start the server";
    $("status-dot").style.background = "var(--red)";
    $("game-message").textContent = "Could not reach the C++ backend. Follow README.md to build and start it.";
  }
}

async function performAction(action, extra = {}) {
  if (requestInProgress) return;
  requestInProgress = true;
  try {
    gameState = await api("/api/action", {
      method: "POST",
      body: JSON.stringify({ action, ...extra })
    });
    render();
  } catch (error) {
    $("game-message").textContent = "The server could not process that action. Check that it is running.";
  } finally {
    requestInProgress = false;
  }
}

function escapeHtml(value) {
  return String(value).replace(/[&<>"']/g, character => ({
    "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;"
  })[character]);
}

function render() {
  if (!gameState) return;
  const player = gameState.player;
  const room = gameState.room;
  $("player-name").textContent = player.name;
  $("health-value").textContent = player.health;
  $("health-bar").style.width = `${player.health}%`;
  $("health-bar").style.background = player.health <= 30
    ? "linear-gradient(90deg,#a12f3d,#e05b65)" : "linear-gradient(90deg,#8c3f4b,#d26c6b)";
  $("score-value").textContent = player.score;
  $("room-name").textContent = room.name;
  $("room-description").textContent = room.description;
  $("art-label").textContent = room.name.toUpperCase();
  $("room-art").dataset.room = room.id;
  const roomNumber = ({ foyer: 1, library: 2, basement: 3, secret: 4 })[room.id] || 1;
  $("room-index").textContent = `${String(roomNumber).padStart(2, "0")} / 04`;
  $("game-message").textContent = gameState.message;

  $("inventory-count").textContent = `${player.inventory.length} ITEM${player.inventory.length === 1 ? "" : "S"}`;
  $("inventory").innerHTML = player.inventory.length
    ? player.inventory.map(item => `<span class="item-chip">${escapeHtml(item)}</span>`).join("")
    : '<p class="muted">Your pockets are empty.</p>';
  $("potion-button").disabled = !player.inventory.includes("Healing Potion") || gameState.status !== "playing";

  $("exits").innerHTML = room.exits.map(exit =>
    `<button class="exit-button" data-target="${escapeHtml(exit.id)}" ${gameState.status !== "playing" ? "disabled" : ""}><span>${escapeHtml(exit.name)}</span><span class="arrow">↗</span></button>`
  ).join("");
  document.querySelectorAll("[data-target]").forEach(button => {
    button.addEventListener("click", () => performAction("move", { target: button.dataset.target }));
  });

  renderDiscovery(room);
  setObjective("objective-key", player.inventory.includes("Silver Key"));
  setObjective("objective-puzzle", gameState.flags.puzzleSolved);
  setObjective("objective-ghost", gameState.flags.basementGhostDefeated);
  setObjective("objective-relic", player.inventory.includes("Raven Emblem"));
  setObjective("objective-escape", gameState.status === "won");

  if (gameState.status !== "playing") showResult(gameState.status);
  else hideResult();
}

function renderDiscovery(room) {
  const content = $("discovery-content");
  const actions = $("discovery-actions");
  actions.replaceChildren();

  if (room.item) {
    content.innerHTML = `<strong>${escapeHtml(room.item.name)}</strong><p>${escapeHtml(room.item.description)}</p>`;
    addAction(actions, "Collect item", "collect");
  } else if (room.ghost) {
    content.innerHTML = `<strong>${escapeHtml(room.ghost.name)}</strong><p>${escapeHtml(room.ghost.description)}</p><p>${escapeHtml(room.ghost.haunt)}</p>`;
    addAction(actions, "Confront the ghost", "fight");
  } else if (room.puzzle) {
    content.innerHTML = `<strong>Inscription on the desk</strong><p>${escapeHtml(room.puzzle.question)}</p>`;
    const form = document.createElement("form");
    form.className = "puzzle-form";
    form.innerHTML = '<input name="answer" aria-label="Puzzle answer" placeholder="Your answer…" autocomplete="off" required><button type="submit">Try</button>';
    form.addEventListener("submit", event => {
      event.preventDefault();
      const answer = new FormData(form).get("answer").toString();
      performAction("solve", { answer });
    });
    actions.appendChild(form);
    addAction(actions, "Ask for a hint", "hint");
  } else {
    content.innerHTML = "<strong>Quiet… for now</strong><p>The room offers no obvious discovery. Explore other passages and return when you have new items.</p>";
  }
}

function addAction(container, label, action) {
  const button = document.createElement("button");
  button.className = "action-button";
  button.textContent = label;
  button.disabled = gameState.status !== "playing";
  button.addEventListener("click", () => performAction(action));
  container.appendChild(button);
}

function setObjective(id, done) {
  $(id).classList.toggle("done", Boolean(done));
}

function showResult(status) {
  hideResult();
  const overlay = document.createElement("div");
  overlay.className = "overlay";
  overlay.id = "result-overlay";
  const won = status === "won";
  overlay.innerHTML = `<div class="result-card"><p class="eyebrow">${won ? "THE MANOR RELEASES YOU" : "THE HOUSE HAS WON"}</p><h2>${won ? "You Escaped" : "Lost to Ravenwood"}</h2><p>${won ? "You uncovered the manor's secret and made it out alive." : "Your exploration has ended for now. Learn the manor's secrets and try again."}</p><p>Final score: <strong>${gameState.player.score}</strong></p><button id="overlay-restart">↻ Play again</button></div>`;
  document.body.appendChild(overlay);
  $("overlay-restart").addEventListener("click", () => performAction("restart"));
}
function hideResult() {
  const overlay = $("result-overlay");
  if (overlay) overlay.remove();
}

$("potion-button").addEventListener("click", () => performAction("use_potion"));
$("restart-button").addEventListener("click", () => performAction("restart"));
refreshState();
