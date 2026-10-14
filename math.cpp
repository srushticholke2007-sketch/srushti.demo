// Multi-Platform Streaming Usage using the Principle of Inclusion-Exclusion (PIE)
// Platforms: Mobile App (M), Web Platform (W), Smart TV App (T)

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    long long M, W, T;          // viewers on each platform
    long long MW, MT, WT;       // viewers on each pair of platforms
    long long MWT;              // viewers on all three platforms

    cout << "Enter number of viewers on Mobile App (M): ";   cin >> M;
    cout << "Enter number of viewers on Web Platform (W): "; cin >> W;
    cout << "Enter number of viewers on Smart TV App (T): "; cin >> T;
    cout << "Enter viewers common to M and W: ";             cin >> MW;
    cout << "Enter viewers common to M and T: ";             cin >> MT;
    cout << "Enter viewers common to W and T: ";             cin >> WT;
    cout << "Enter viewers common to M, W and T: ";          cin >> MWT;

    // ---- Validation: the data must be logically consistent ----
    bool ok = MWT >= 0 && MWT <= MW && MWT <= MT && MWT <= WT &&
              MW <= M && MW <= W && MT <= M && MT <= T && WT <= W && WT <= T;
    // each "only" region must be non-negative
    long long onlyMW = MW - MWT, onlyMT = MT - MWT, onlyWT = WT - MWT;
    long long onlyM = M - onlyMW - onlyMT - MWT;
    long long onlyW = W - onlyMW - onlyWT - MWT;
    long long onlyT = T - onlyMT - onlyWT - MWT;
    if (!ok || onlyM < 0 || onlyW < 0 || onlyT < 0) {
        cout << "\nInvalid input: the overlaps are inconsistent with platform totals.\n";
        return 1;
    }

    // ---- PIE: |M U W U T| ----
    long long unique = M + W + T - MW - MT - WT + MWT;

    long long exactlyOne   = onlyM + onlyW + onlyT;
    long long exactlyTwo   = onlyMW + onlyMT + onlyWT;
    long long exactlyThree = MWT;
    long long multiDevice  = exactlyTwo + exactlyThree;

    auto pct = [&](long long x) {
        return unique ? (100.0 * x / unique) : 0.0;
    };

    cout << fixed << setprecision(2);
    cout << "\n========== RESULTS ==========\n";
    cout << "Total unique viewers (PIE)          : " << unique << "\n\n";

    cout << "--- Viewers on exactly one platform ---\n";
    cout << "Mobile only : " << onlyM << " (" << pct(onlyM) << "%)\n";
    cout << "Web only    : " << onlyW << " (" << pct(onlyW) << "%)\n";
    cout << "TV only     : " << onlyT << " (" << pct(onlyT) << "%)\n";

    cout << "\n--- Overlaps between platforms (exactly two) ---\n";
    cout << "Mobile & Web only : " << onlyMW << " (" << pct(onlyMW) << "%)\n";
    cout << "Mobile & TV only  : " << onlyMT << " (" << pct(onlyMT) << "%)\n";
    cout << "Web & TV only     : " << onlyWT << " (" << pct(onlyWT) << "%)\n";
    cout << "All three         : " << MWT    << " (" << pct(MWT)    << "%)\n";

    cout << "\n--- Usage patterns ---\n";
    cout << "Single-platform viewers : " << exactlyOne   << " (" << pct(exactlyOne)   << "%)\n";
    cout << "Two-platform viewers    : " << exactlyTwo   << " (" << pct(exactlyTwo)   << "%)\n";
    cout << "Three-platform viewers  : " << exactlyThree << " (" << pct(exactlyThree) << "%)\n";
    cout << "Multi-device viewers    : " << multiDevice  << " (" << pct(multiDevice)  << "%)\n";
    cout << "Duplicate count removed : " << (M + W + T - unique) << "\n";

    // ---- Simple recommendations ----
    cout << "\n--- Recommendations ---\n";
    long long best = max(M, max(W, T));
    string top = (best == M) ? "Mobile App" : (best == W) ? "Web Platform" : "Smart TV App";
    cout << "* Largest audience is on the " << top << " - prioritise its development.\n";

    long long maxOverlap = max(onlyMW, max(onlyMT, onlyWT));
    if (maxOverlap > 0) {
        string pair = (maxOverlap == onlyMW) ? "Mobile & Web"
                    : (maxOverlap == onlyMT) ? "Mobile & TV" : "Web & TV";
        cout << "* Strongest overlap is " << pair
             << " - add cross-device features (continue watching, synced watchlist).\n";
    }
    if (pct(multiDevice) >= 30.0)
        cout << "* Many multi-device users - offer bundled plans and cross-platform recommendations.\n";
    else
        cout << "* Most users stick to one platform - run campaigns to encourage trying other platforms.\n";

    long long smallest = min(M, min(W, T));
    string low = (smallest == M) ? "Mobile App" : (smallest == W) ? "Web Platform" : "Smart TV App";
    cout << "* Lowest usage is on the " << low << " - target promotions there.\n";

    return 0;
}