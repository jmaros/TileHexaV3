#pragma once
// TileSolver.h
// Shared types and solver API for the hexagonal calendar puzzle.
//
// Included by both Hexa3DApp.cpp and TileSolver.cpp so that AppState and
// its dependencies are defined in exactly one place.

#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstdio>

// ── grid geometry constants (defined once in Hexa3DApp.cpp) ─────────────
extern const float R;
extern const float sx;
extern const float sy;

// ── Cell ─────────────────────────────────────────────────────────────────
struct Cell { int type, value; };
enum { CT_BASE = -1, CT_EMPTY = 0, CT_MONTH = 1, CT_WDAY = 2, CT_DATE = 3 };

// ── HexTile ───────────────────────────────────────────────────────────────
struct HexTile {
	int   row, col;
	float x, y, z;
	bool  highlight;
	bool  protectedDate;
	Cell  content;
};

// ── PieceDefinition ───────────────────────────────────────────────────────
struct PieceDefinition {
	char                               label;
	std::vector<std::pair<float,float>> offsets;
	float                              r, g, b;
};

// ── PieceState ────────────────────────────────────────────────────────────
struct PieceState {
	const PieceDefinition*              def = nullptr;
	std::vector<std::pair<float,float>> offsets;
	float x        = 0.0f;
	float y        = 0.0f;
	bool  placed   = false;
	std::vector<int>                    occupiedCells;
	float homeX    = 0.0f;
	float homeY    = 0.0f;
	std::vector<std::pair<float,float>> homeOffsets;
	std::vector<std::pair<float,float>> ghostCenters;
};

// ── PieceSnapshot ─────────────────────────────────────────────────────────
struct PieceSnapshot {
	float x        = 0.0f;
	float y        = 0.0f;
	bool  placed   = false;
	std::vector<std::pair<float,float>> offsets;
	std::vector<int>                    occupiedCells;
	std::vector<std::pair<float,float>> ghostCenters;
};

// ── MoveHistoryEntry ──────────────────────────────────────────────────────
struct MoveHistoryEntry {
	int           pieceIndex = -1;
	PieceSnapshot before;
	PieceSnapshot after;
};

// ── PlacementCandidate ────────────────────────────────────────────────────
struct PlacementCandidate {
	bool valid        = false;
	bool outsideBoard = false;
	std::vector<int>  cells;
	float snapX       = 0.0f;
	float snapY       = 0.0f;
};

// ── AppState ──────────────────────────────────────────────────────────────
struct AppState {
	std::vector<HexTile>*               tiles = nullptr;
	std::vector<PieceState>             pieces;
	std::vector<int>                    occupancy;
	int   selectedPiece   = -1;
	int   dragPiece       = -1;
	bool  dragging        = false;
	float dragDx          = 0.0f;
	float dragDy          = 0.0f;
	bool  savedPlaced     = false;
	float savedX          = 0.0f;
	float savedY          = 0.0f;
	std::vector<std::pair<float,float>> savedOffsets;
	std::vector<int>                    savedCells;
	std::vector<std::pair<float,float>> savedGhostCenters;
	PieceSnapshot                       beforeDragSnapshot;
	std::pair<float,float>              dragLocal{ 0.0f, 0.0f };
	PlacementCandidate                  target;
	bool  solved          = false;
	bool  showHelp        = false;
	int   protectedCellCount = 0;
	std::vector<MoveHistoryEntry>       undoStack;
	std::vector<MoveHistoryEntry>       redoStack;
	// ── solver state ──────────────────────────────────────────────────────
	std::vector<PieceSnapshot>          presolveState;        // piece snapshot before the last solver run
	std::vector<MoveHistoryEntry>       presolveUndoStack;    // undo history saved before solver runs
	std::vector<MoveHistoryEntry>       presolveRedoStack;    // redo history saved before solver runs
	bool  solverRunning   = false;  // true while the label frame is displayed (before actual search)
	bool  solverPending   = false;  // true after prepareSolve: executePendingSolve will fire next tick
	bool  solverRandomize = false;  // true = randomized mode, false = deterministic
	int   solverSkipCount = 0;      // how many solutions to skip (enumerate)
	std::string solverLabel{};      // "Searching…" / "Thinking…" / "Solving…"
};

// ── Solver API ────────────────────────────────────────────────────────────

// Convenience alias
using Offsets = std::vector<std::pair<float,float>>;

// Build the set of unique orientations (up to 12) for a piece.
void generateOrientations(const Offsets& base, std::vector<Offsets>& out);

// Restore the board to the snapshot taken just before the last solver run.
void restorePresolveState(AppState& app);

// Phase 1 (call from key handler): pick a label, set solverPending=true,
// solverRunning=true so the banner renders on the very next frame.
void prepareSolve(AppState& app, bool randomize);

// Phase 2 (call from render loop AFTER glfwSwapBuffers): if solverPending,
// run the actual backtracking and clear the pending flag.
void executePendingSolve(AppState& app);
