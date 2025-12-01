# Mini C++ ML Library – Ideen & Visualisierungskonzept

Dies ist eine Ideensammlung für eine kleine, von Grund auf implementierte ML-Bibliothek in C++.  
Ziel: Modelle trainieren, debuggen und visualisieren ähnlich wie in scikit-learn, inkl. Data Preprocessing und Monitoring.

---

## 1. Kern-Modelle

| Modell | Beschreibung | Nützliche Visualisierungen |
|--------|--------------|----------------------------|
| **Lineare Regression** | Gradient Descent, MSE Loss | Scatterplot der Daten + Regressionslinie, Loss über Iterationen, Parameterverlauf (θ₀, θ₁), 2D Fehlerlandschaft |
| **Binäre Klassifikation** | Logistic Regression, einfache Decision Boundary | Scatterplot nach Klasse, Entscheidungsgrenze / Heatmap der Wahrscheinlichkeit, Confusion Matrix, ROC-Kurve |
| **Clustering** | K-Means, evtl. hierarchisches Clustering | Scatterplot mit Clusterfarben, Centroid-Positionen, Silhouette Score Histogramm, dendrogram (optional) |
| **Zeitreihen Regression** | Lineare / einfache Regressionsmodelle | Line Plot der Zeitreihe vs Prediction, Fehlerverlauf, Rolling Average Overlay |
| **Random Forest / Decision Trees** | Ensemble Methoden | Feature Importance Barplot, Decision Surface (2D), OOB Error Verlauf |
| **Support Vector Machines (SVM)** | Klassifikation | Scatterplot mit Support Vectors markiert, Decision Boundary / Surface |

---

## 2. Data Preprocessing & Exploration

| Aufgabe | Mögliche Visualisierung / Tool |
|---------|-------------------------------|
| Feature Distribution | Histogramme, Boxplots / Violinplots |
| Korrelationen | Scatter Matrix / Pairplots, Heatmap |
| Ausreißer Detection | Boxplots, Scatterplot Highlight |
| Missing Values | Heatmap / Tabelle |
| Scaling / Normalization | Histogramme Vorher / Nachher |
| Encoding | Überblick über kategoriale Feature Verteilung |

---

## 3. Debugging & Training Monitoring

- **Loss / Error Plot über Iterationen**
- **Parameter / Weight Verlauf** (z. B. θ₀, θ₁)
- **Live Scatterplots / Decision Boundary Updates**
- **Interaktive Controls** (z. B. Learning Rate, Epochs, Regularization)
- **Highlight Fehlklassifizierte Punkte**
- **Zoom / Pan** für 2D-Datenvisualisierung

---

## 4. Visualisierungstypen für C++ / OpenGL

| Typ | Beschreibung | Zweck |
|-----|--------------|-------|
| Scatterplot | Punkte in 2D oder 3D | Datenverteilung, Cluster, Klassifikation |
| Linienplot | Lineare Regression, Zeitreihe | Trend, Vorhersage, Loss Verlauf |
| Heatmap | Entscheidungsflächen, Wahrscheinlichkeiten | Wahrscheinlichkeit, Cluster, Fehler |
| Barplot | Feature Importance, Parameterwerte | Interpretation, Debugging |
| Histogramm | Feature Distribution | Preprocessing, Normalization Check |
| Confusion Matrix | Rasterplot | Klassifikationsqualität |
| Dendrogram | Hierarchisches Clustering | Cluster Struktur |

---

## 5. Roadmap / Priorität

1. **Grundlagen:**
   - Lineare Regression + Gradient Descent
   - Scatterplot + Regressionslinie
   - Loss-Plot über Iterationen
2. **Binary Classification:**
   - Scatterplot mit Entscheidungsgrenze
   - Confusion Matrix
   - Probability Heatmap
3. **Clustering:**
   - K-Means
   - Scatterplot + Centroids
   - Silhouette Score Histogramm
4. **Zeitreihen Regression**
   - Line Plot Prediction vs Ground Truth
5. **Erweiterte Modelle (optional)**
   - Random Forest / Decision Trees
   - Feature Importance, Decision Surface
   - SVM: Support Vectors visualisieren
6. **Data Preprocessing Tools**
   - Histogramme, Boxplots, Heatmaps
   - Missing Values Check
   - Feature Scaling / Normalization

---

## 6. Hinweise zur Implementierung in C++

- Verwende **OpenGL + GLFW / SDL2** für Fenster & Rendering
- Optional: **ImGui** für interaktive Controls (Sliders, Buttons)
- Data Management: **Vectorisierte Matrizen / Eigen Library** für Performance
- Live-Update während Training: VBOs für Scatterplots / Linienplots aktualisieren
- Start einfach: Scatterplots & Linienplots, später Heatmaps und Barplots

---

## 7. Ziel

- Ein **leicht verständliches ML-Debug-Framework** in C++
- Von Grund auf implementierte Modelle
- Live-Visualisierung & interaktive Parametersteuerung
- Schrittweise Erweiterung: Regression → Klassifikation → Clustering → Random Forest / SVM → Zeitreihen
