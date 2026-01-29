# Product Configurator - Complete Beginner's Guide

 > **Welcome!** This guide assumes you're brand new to Unreal Engine. Every step is explained in detail with screenshots descriptions and tips.

 ---

 ## 📚 Table of Contents

 ### Part 1: Getting Started (For Complete Beginners)
 1. [What Is This Project?](#what-is-this-project)
 2. [What You'll Need](#what-youll-need)
 3. [Installing Unreal Engine](#installing-unreal-engine)
 4. [Opening The Project](#opening-the-project)
 5. [Understanding The Interface](#understanding-the-interface)
 6. [Your First Export Test](#your-first-export-test)

 ### Part 2: Understanding The System
 7. [How The Configurator Works](#how-the-configurator-works)
 8. [What Are Variant Sets?](#what-are-variant-sets)
 9. [What Does The Export Do?](#what-does-the-export-do)

 ### Part 3: Customizing For Your Product
 10. [Swapping The Guitar Model For A Car (Or Any Product)](#swapping-the-guitar-model-for-a-car)
 11. [Adding New Variant Sets](#adding-new-variant-sets)
 12. [Removing Variant Sets](#removing-variant-sets)
 13. [Editing Existing Variants](#editing-existing-variants)
 14. [Organizing Your Project](#organizing-your-project)

 ### Part 4: Advanced Customization
 15. [Changing Where PDFs Are Saved](#changing-where-pdfs-are-saved)
 16. [Changing File Names](#changing-file-names)
 17. [Customizing The PDF Layout](#customizing-the-pdf-layout)

 ### Part 5: Troubleshooting & Help
 18. [Common Problems & Solutions](#common-problems--solutions)
 19. [Where To Get Help](#where-to-get-help)

 ---

 ## Part 1: Getting Started (For Complete Beginners)

 ---

 ### What Is This Project?

 This is a **Product Configurator** built in Unreal Engine. Think of it like a 3D customizer you might see on a car manufacturer's website, but it runs in real-time 3D.

 **What it does:**
 - Shows a 3D product (currently a guitar)
 - Lets users customize different parts (color, shape, accessories)
 - Exports a PDF report showing what was selected
 - Can be adapted for ANY product (cars, furniture, clothing, etc.)

 **Current Setup:**
 - **Product:** Guitar
 - **11 Customization Options:** Lighting, Camera, Body Shape, Body Color, Hardware, Head Shape, Pickups, Pick Guard, Fret Inlays, Fret Board, Tremolo

 ---

 ### What You'll Need

 #### Required Software (All Free*)

 1. **Unreal Engine 5.5.4**
    - Download from: Epic Games Launcher
    - Size: ~40GB
    - *Free for learning/evaluation

 2. **Visual Studio 2022 Community Edition** (for C++ editing)
    - Download from: https://visualstudio.microsoft.com/
    - Size: ~10GB
    - *Free for individuals
    - **Important:** When installing, select "Game Development with C++" workload

 3. **Python 3.x** (for PDF generation)
    - Download from: https://www.python.org/downloads/
    - Size: ~100MB
    - *Free and open source
    - **Important:** Check "Add Python to PATH" during installation

 #### Your Computer Should Have:
 - **CPU:** Modern quad-core or better
 - **RAM:** 16GB minimum (32GB recommended)
 - **GPU:** NVIDIA GTX 1070 or AMD equivalent or better
 - **Storage:** 100GB free space (SSD recommended)
 - **OS:** Windows 10/11 (64-bit)

 ---

 ### Installing Unreal Engine

 #### Step 1: Get Epic Games Launcher

 1. Go to: https://www.epicgames.com/store/
 2. Click **"Get Epic Games"** in the top right
 3. Download and install the launcher
 4. Create an Epic Games account (free)

 #### Step 2: Install Unreal Engine 5.5.4

 1. **Open Epic Games Launcher**
 2. Click **"Unreal Engine"** tab on the left
 3. Click **"Library"** at the top
 4. Click the **yellow "+" button** next to ENGINE VERSIONS
 5. Select **"5.5.4"** from the dropdown
 6. Click **"Install"**
 7. Choose install location (needs 40GB)
 8. Wait for download (can take 30min - 2 hours depending on internet speed)

 #### Step 3: Verify Installation

 1. Once installed, you'll see "5.5.4" in your Library
 2. Click **"Launch"** next to 5.5.4
 3. Unreal Engine should open to the project browser
 4. Close it for now (we'll open your project next)

 ---

 ### Opening The Project

 #### Step 1: Locate The Project Files

 1. Open **File Explorer** (Windows key + E)
 2. Navigate to: `F:\0personal\ProductConfigurator\`
 3. You should see these files:
    - `ProductConfigurator.uproject` (Unreal Engine project file)
    - `Content` folder (all 3D assets, levels, blueprints)
    - `Saved` folder (exports go here)
    - `Source` folder (C++ code)

 #### Step 2: Open The Project

 **Method 1 - Double Click:**
 1. Double-click `ProductConfigurator.uproject`
 2. Unreal Engine will launch automatically

 **Method 2 - From Epic Games Launcher:**
 1. Open Epic Games Launcher
 2. Go to **Unreal Engine → Library**
 3. Click **"Add Existing"** (top right, small button)
 4. Browse to `F:\0personal\ProductConfigurator\ProductConfigurator.uproject`
 5. Click **"Open"**
 6. Project appears in your library - click **"Open"**

 #### Step 3: Wait For Project To Load

 1. First time opening takes 2-5 minutes
 2. You'll see "Loading..." screens
 3. If asked to rebuild modules, click **"Yes"**
 4. If asked to convert/upgrade, click **"Skip"** (already correct version)

 #### Step 4: You're In!

 Once loaded, you should see:
 - **Viewport** (big 3D window in center)
 - **Content Browser** (bottom panel with folders)
 - **Details Panel** (right side)
 - **Outliner** (right side, shows all objects in scene)

 ---

 ### Understanding The Interface

 Let me explain what you're looking at:

 #### Main Areas (Think of it like Photoshop or Excel)

 ```
 ┌─────────────────────────────────────────────────────────┐
 │  MENU BAR (File, Edit, Window, Tools...)               │
 ├─────────────────────────────────────────────────────────┤
 │  TOOLBAR (Play, Save, Build, etc.)                     │
 ├────────────┬────────────────────────────┬───────────────┤
 │            │                            │               │
 │  OUTLINER  │      VIEWPORT (3D)         │   DETAILS     │
 │            │                            │               │
 │  (List of  │   Your 3D scene            │   (Properties │
 │   objects) │   Shows the guitar         │    of         │
 │            │                            │    selected   │
 │            │                            │    object)    │
 ├────────────┴────────────────────────────┴───────────────┤
 │  CONTENT BROWSER (All your assets/files)                │
 └─────────────────────────────────────────────────────────┘
 ```



 ---

 ### Your First Export Test

 Let's make sure the PDF export system works!

 #### Step 1: Open The Main Level

 1. In **Content Browser** (bottom panel)
 2. Click on **"Content"** folder
 3. Navigate to: `ProductAssets → Levels`
 4. **Double-click** `Main` (shows a level icon)
 5. The guitar scene will load in the Viewport

 #### Step 2: Open The Output Log

 1. Click **"Window"** in the menu bar (top)
 2. Hover over **"Developer Tools"**
 3. Click **"Output Log"**
 4. A new panel opens at the bottom
 5. This shows messages from Unreal (like a console)

 #### Step 3: Open Python Console

 1. In the **Output Log** panel you just opened
 2. Look for tabs at the top: "Output Log" | "Message Log" | "Python"
 3. Click the **"Python"** tab
 4. You now have a Python command line

 #### Step 4: Run The Test Code

 1. Copy this code EXACTLY (triple-click to select all):

 ```python
 import unreal

 # Get the actor
 actors = unreal.get_editor_subsystem(unreal.EditorActorSubsystem).get_all_level_actors()
 variant_actor = None
 for actor in actors:
     if actor.get_class().get_name() == "LevelVariantSetsActor":
         variant_actor = actor
         break

 if variant_actor:
     print("✅ Found the guitar configurator!")
     result = unreal.ConfigurationExportLibrary.export_variant_sets_to_pdf(
         variant_actor,
         "MyFirstTest"
     )
     success, pdf_path, error = result
     if success:
         print(f"✅✅✅ SUCCESS! PDF Created!")
         print(f"Location: {pdf_path}")
     else:
         print(f"❌ Error: {error}")
 else:
     print("❌ Could not find LevelVariantSetsActor")
 ```

 2. **Paste** into the Python console (Ctrl+V)
 3. **Press Enter**
 4. Wait 2-3 seconds

 #### Step 5: Check The Results

 You should see:
 ```
 ✅ Found the guitar configurator!
 ✅✅✅ SUCCESS! PDF Created!
 Location: ../../../../../0personal/ProductConfigurator/Saved/PDFs/MyFirstTest_2026-01-28_...pdf
 ```

 #### Step 6: Find Your PDF

 1. Open **File Explorer**
 2. Go to: `F:\0personal\ProductConfigurator\Saved\PDFs\`
 3. You'll see your PDF file!
 4. **Double-click to open it**

 **What's Inside:**
 - Configuration name: "MyFirstTest"
 - Timestamp
 - List of 11 variant sets with their current selections
 - Example: "Body Color: Black", "Pickups: Black", etc.

 ---

 ## Part 2: Understanding The System

 ---

 ### How The Configurator Works

 Think of it like building a custom pizza:

 1. **Base (3D Model):** The guitar in the scene
 2. **Toppings (Variants):** Different colors, shapes, parts you can swap
 3. **Menu (Variant Sets):** Groups of related options (like "Cheese Type", "Toppings", "Size")
 4. **Receipt (PDF Export):** Shows exactly what you picked

 **Technical Flow:**
 ```
 User Clicks Option
       ↓
 Variant Manager Swaps 3D Parts
       ↓
 User Clicks "Export PDF"
       ↓
 System Reads Active Variants
       ↓
 Creates JSON File (data)
       ↓
 Python Converts JSON → PDF
       ↓
 PDF Saved To Disk
 ```

 ---

 ### What Are Variant Sets?

 **Simple Explanation:**
 A Variant Set is a GROUP of related options where you can pick ONE at a time.

 **Example: Body Color Variant Set**
 - Contains: Black, White, Red, Blue, Sunburst, Natural, Pink, Metallic
 - You can pick: ONE color at a time
 - Picking "Red" automatically deselects "Black"

 **Current Variant Sets In This Project:**

 | Variant Set Name | What It Controls | Example Options |
 |-----------------|------------------|-----------------|
 | Lighting | Scene lighting mood | NeutralWarmCold, Bright, Dark |
 | Camera | View angle | Overview, Close-up, Side View, Top View |
 | Body Shape | Guitar body style | Strat Type, Les Paul Type, Telecaster Type |
 | Body Color | Paint color | Black, White, Red, Sunburst, etc. |
 | Hardware | Metal parts finish | Chrome, Gold, Black |
 | Head Shape | Headstock design | Type A, Type B, Type C |
 | Pickups | Pickup color | Black, White |
 | Pick Guard | Guard color/style | Black, White, None |
 | Fret Inlays | Fret marker style | Dots, Blocks, Pearl |
 | Fret Board | Fretboard wood | Dark, Light, Maple |
 | Tremolo | Tremolo arm | On, Off |

 ---

 ### What Does The Export Do?

 The export system creates a **PDF report** showing the current configuration.

 **What Gets Exported:**
 - Which variant is currently ACTIVE in each set
 - Timestamp of when export was created
 - Configuration name you provide

 **What Does NOT Get Exported:**
 - Inactive variants
 - Variants from multiple sets at once
 - 3D model data or screenshots (just text list)

 **Example Output:**
 ```
 Product Configuration Summary
 Configuration: Guitar_Configuration
 Timestamp: 2026-01-28 04:03:54

 Selected Variants:
   • Lighting: NeutralWarmCold
   • Camera: Overview
   • Body Shape: Strat Type
   • Body Color: Black
   • Hardware: Chrome
   • Head Shape: Type A
   • Pickups: Black
   • Pick Guard: Black
   • Fret Inlays: Pearl
   • Fret Board: Light
   • Tremolo: On
 ```

 ---

 ## Part 3: Customizing For Your Product

 ---

 ### Swapping The Guitar Model For A Car

 Let's replace the entire guitar with a car! This process works for ANY 3D model.

 ---

 #### PHASE 1: Prepare Your Car Model

 ##### Step 1: Get Or Create A 3D Car Model

 **Option A - Free Models:**
 - **Quixel Bridge** (free, built into Unreal)
 - **Unreal Engine Marketplace** (many free assets)
 - **Sketchfab** (download as FBX)

 **Option B - Your Own Model:**
 - Export from: Blender, Maya, 3ds Max, etc.
 - Format: **FBX** or **USD** (FBX is easier)
 - Include materials/textures

 **Requirements:**
 - ✅ Clean geometry (no overlapping faces)
 - ✅ Proper scale (real-world meters: car = ~4-5m long)
 - ✅ Centered pivot point
 - ✅ Materials applied

 ##### Step 2: Import The Car Into Unreal

 1. Open your project in Unreal Engine
 2. In **Content Browser**, navigate to: `Content → ProductAssets`
 3. **Right-click** in empty space → **"Import to..."**
 4. Browse to your car model (`.fbx` file)
 5. **Import Settings Window Opens**

 **Important Settings:**
 - ✅ **Import Mesh:** Checked
 - ✅ **Import Materials:** Checked
 - ✅ **Import Textures:** Checked
 - ⚠️ **Skeleton:** None (unless it's animated)
 - ⚠️ **Auto Generate Collision:** Checked
 - Click **"Import All"**

 6. Wait for import (can take 30 seconds)
 7. You'll see new assets appear:
    - `Car_Model` (the mesh)
    - `M_Car_Material` (materials)
    - Textures

 ##### Step 3: Test The Import

 1. **Drag the car mesh** from Content Browser into the Viewport
 2. It should appear in your scene
 3. Use **W, E, R keys** to move/rotate/scale
 4. Delete it for now (select and press Delete key)

 ---

 #### PHASE 2: Break Down The Car Into Parts

 For the configurator to work, you need to separate customizable parts.

 ##### Understanding Part Separation

 **Example Guitar Breakdown:**
 - Body (separate mesh)
 - Neck (separate mesh)
 - Pickups (separate mesh)
 - Hardware (separate mesh)

 **Example Car Breakdown:**
 - Car Body (main)
 - Wheels (4 separate or 1 swappable)
 - Doors (left, right)
 - Hood
 - Trunk
 - Bumpers (front, back)
 - Interior (seats, dashboard)
 - Windows

 ##### Step 1: Check If Your Model Is Already Separated

 1. Import your car model
 2. **Double-click** the imported static mesh
 3. Static Mesh Editor opens
 4. Look at **left panel** → "Static Mesh Editor"
 5. Check "LOD 0" → "Elements"

 **If you see multiple "Material Slots":**
 - ✅ Model has multiple materials = partially separated
 - You can work with this!

 **If you see only 1 material:**
 - ⚠️ Everything is one piece
 - You'll need to separate it

 ##### Step 2A: If Already Separated

 Great! Your model has multiple material slots.

 **What this means:**
 - Different parts have different materials
 - You can swap materials per part
 - Example: Material Slot 0 = Body, Slot 1 = Wheels, Slot 2 = Windows

 **Next:** Skip to Phase 3

 ##### Step 2B: If NOT Separated (One Solid Mesh)

 You'll need to split it into parts.

 **Option 1 - Use Modeling Tools (Easier):**

 1. **Enable Modeling Tools Plugin:**
    - Edit → Plugins
    - Search "Modeling"
    - Check "Modeling Tools Editor Mode"
    - Restart Unreal Engine

 2. **Switch to Modeling Mode:**
    - Top left of viewport → Click "Selection Mode" dropdown
    - Select "Modeling" mode

 3. **Use PolyGroup Tools:**
    - Select your car in viewport
    - In left panel: "PolyGroup" tools
    - Click "Auto Group" → "Generate"
    - This separates by material/smoothing

 4. **Split to Separate Meshes:**
    - Use "Separate" tool
    - Choose polygroups to split out

 **Option 2 - Go Back to 3D Software (Professional):**

 1. Open model in Blender/Maya/Max
 2. Separate parts manually (Select faces → Separate → By Material)
 3. Export each part as separate FBX
 4. Import back to Unreal

 ---

 #### PHASE 3: Create The Car Actor Blueprint

 ##### Step 1: Create A New Blueprint

 1. In **Content Browser**
 2. Navigate to: `Content → ProductAssets`
 3. **Right-click** in empty space
 4. **"Blueprint Class"**
 5. Choose **"Actor"**
 6. Name it: `BP_Car` (or whatever you want)
 7. **Double-click** to open it

 ##### Step 2: Add The Car Mesh Components

 1. Blueprint Editor opens
 2. Look at **left panel:** "Components"
 3. You'll see "DefaultSceneRoot"
 4. Click **"Add"** button (top left, green button)
 5. Search for "Static Mesh"
 6. Click **"Static Mesh"**
 7. A new component appears: "StaticMesh"

 **Rename it:**
 1. **Right-click** "StaticMesh" in Components panel
 2. **"Rename"**
 3. Name it: `CarBody`
 4. Press Enter

 **Assign The Mesh:**
 1. With `CarBody` selected
 2. Look at **Details Panel** (right side)
 3. Find "Static Mesh" property (near top)
 4. Click dropdown → select your imported car mesh
 5. The car appears in the Blueprint viewport!

 ##### Step 3: Add More Components For Each Part

 Repeat for each customizable part:

 **Example - Adding Wheels:**
 1. Click **"Add"** → "Static Mesh"
 2. Rename to: `Wheel_FrontLeft`
 3. Assign wheel mesh in Details
 4. Use **Move Tool (W key)** to position it

 **Add all parts:**
 - CarBody (main mesh)
 - Wheel_FrontLeft
 - Wheel_FrontRight  
 - Wheel_RearLeft
 - Wheel_RearRight
 - Hood
 - Doors
 - Bumper_Front
 - Bumper_Rear
 - (etc.)

 **Tips:**
 - Make sure each component is **child of DefaultSceneRoot**
 - Use **Snap** tools to align precisely (top toolbar)
 - Test scale by comparing to Unreal's default cube (1m cube)

 ##### Step 4: Compile And Save

 1. Click **"Compile"** button (top left, big hammer icon)
 2. Wait for success message
 3. Click **"Save"** button (next to Compile)
 4. Close Blueprint Editor

 ---

 #### PHASE 4: Replace Guitar With Car In The Level

 ##### Step 1: Open The Main Level

 1. Content Browser → `ProductAssets → Levels`
 2. Double-click `Main`

 ##### Step 2: Find The Guitar Actor

 1. Look in **Outliner** (right panel)
 2. Find the guitar actor (might be named `BP_Guitar` or similar)
 3. **Click** to select it
 4. The guitar will highlight in viewport

 ##### Step 3: Delete The Guitar

 1. With guitar selected
 2. Press **Delete** key
 3. Guitar disappears

 ##### Step 4: Add Your Car

 1. In **Content Browser**, find your `BP_Car` blueprint
 2. **Drag** `BP_Car` into the viewport
 3. Drop it in the scene
 4. Use **W, E, R keys** to position/rotate/scale

 **Position Tips:**
 - Place at origin (0, 0, 0) for easy camera setup
 - Make sure it's sitting on the ground
 - Check all angles (Top, Side, Front views)

 ##### Step 5: Save The Level

 1. Press **Ctrl + S**
 2. Or click "Save Current Level" in toolbar

 ---

 #### PHASE 5: Update The Variant Sets

 Now we need to change variant sets from guitar options to car options.

 ##### Step 1: Open Variant Manager

 1. Menu bar → **Window**
 2. Hover over **Cinematics**
 3. Click **Variant Manager**
 4. Panel opens (usually bottom of screen)

 ##### Step 2: Find The Level Variant Sets Actor

 1. In **Outliner**, look for: `LevelVariantSetsActor`
 2. **Click** to select it
 3. In **Details Panel**, find "Level Variant Sets" property
 4. Note the asset: `/Game/ProductAssets/VariantSet`

 ##### Step 3: Open The Variant Set Asset

 **Method 1:**
 1. In Details, **double-click** the asset path
 2. Variant Set Editor opens

 **Method 2:**
 1. Content Browser → `ProductAssets`
 2. Find `VariantSet` asset (has special icon)
 3. **Double-click** it

 ##### Step 4: Delete Old Guitar Variant Sets

 You'll see a list of variant sets on the left:
 - Lighting
 - Camera
 - Body Shape
 - Body Color
 - (etc.)

 **Delete the ones you don't need:**
 1. **Right-click** "Body Shape"
 2. **"Delete Variant Set"**
 3. Confirm: Click "Yes"
 4. Repeat for:
    - Pickups
    - Pick Guard
    - Fret Inlays
    - Fret Board
    - Tremolo
    - (any other guitar-specific sets)

 **Keep these:**
 - Lighting (universal)
 - Camera (universal)

 ##### Step 5: Create New Car Variant Sets

 Let's add car-specific variant sets.

 **Example: Body Color Variant Set**

 1. Click **"+ Variant Set"** button (top left)
 2. A new set appears: "Variant Set"
 3. **Right-click** it → "Rename"
 4. Type: `BodyColor`
 5. Press Enter

 **Add Variants To It:**

 1. With `BodyColor` selected
 2. Click **"+ Variant"** button
 3. A new variant appears: "Variant"
 4. **Right-click** → "Rename" → Type: `Red`
 5. Repeat for other colors:
    - Black
    - White
    - Blue
    - Silver
    - (etc.)

 **Assign What Each Variant Changes:**

 1. Select the `Red` variant
 2. Look at the **bottom panel** (Captured Properties)
 3. Click **"+ Actor"**
 4. In the popup, select your `BP_Car` from the scene
 5. Click **"OK"**
 6. Another popup: "Capture Properties"
 7. **Expand** the CarBody component tree
 8. Find **"Material Overrides"** or **"Materials"**
 9. **Check** the box next to it
 10. Click **"OK"**

 **Set The Material:**

 1. With Red variant still selected
 2. In Captured Properties, you'll see: `BP_Car → CarBody → Materials`
 3. Click the dropdown
 4. Select your red material (or create one first)

 **Repeat For Other Variants:**
 - Select `Black` variant → capture materials → set black material
 - Select `White` variant → capture materials → set white material
 - (etc.)

 ##### Step 6: Create More Variant Sets

 Repeat the process for:

 **Wheel Style:**
 - Sport Wheels
 - Off-Road Wheels
 - Classic Wheels

 **Interior:**
 - Leather Black
 - Leather Brown
 - Fabric Gray

 **Trim:**
 - Chrome
 - Matte Black
 - Carbon Fiber

 **Etc.**

 ##### Step 7: Test The Variants

 1. In Variant Manager, click different variants
 2. Watch the car update in the viewport
 3. Try different combinations
 4. Make sure everything works

 ##### Step 8: Save Everything

 1. Click **Save** in Variant Manager
 2. Press **Ctrl + S** to save level
 3. Click **File → Save All** to save everything

 ---

 #### PHASE 6: Update The Export

 The export should automatically work with your new variant sets!

 ##### Test It:

 1. Open Python console (Window → Developer Tools → Output Log → Python tab)
 2. Run the test code from earlier:

 ```python
 import unreal

 actors = unreal.get_editor_subsystem(unreal.EditorActorSubsystem).get_all_level_actors()
 variant_actor = None
 for actor in actors:
     if actor.get_class().get_name() == "LevelVariantSetsActor":
         variant_actor = actor
         break

 if variant_actor:
     result = unreal.ConfigurationExportLibrary.export_variant_sets_to_pdf(
         variant_actor,
         "CarConfiguration"
     )
     success, pdf_path, error = result
     if success:
         print(f"✅ PDF Created: {pdf_path}")
     else:
         print(f"❌ Error: {error}")
 ```

 3. Check the PDF - it should now list your car variant sets!

 ---

 ### Adding New Variant Sets

 Let's say you want to add a "Spoiler" variant set.

 #### Step-by-Step:

 ##### Step 1: Create The Spoiler 3D Models

 1. Import 3 different spoiler designs as separate static meshes:
    - `SM_Spoiler_Sport`
    - `SM_Spoiler_GT`
    - `SM_Spoiler_None` (empty/placeholder)

 ##### Step 2: Add Spoiler To Your Car Blueprint

 1. Open `BP_Car` blueprint
 2. Add new Static Mesh component
 3. Name it: `Spoiler`
 4. Don't assign a mesh yet (variants will control this)
 5. Position where spoiler should be
 6. Compile and Save

 ##### Step 3: Open Variant Set Editor

 1. Content Browser → `ProductAssets → VariantSet`
 2. Double-click to open

 ##### Step 4: Create New Variant Set

 1. Click **"+ Variant Set"** button
 2. Rename to: `Spoiler`

 ##### Step 5: Add Variants

 1. With Spoiler selected
 2. Add variant: `Sport` (+ Variant button)
 3. Add variant: `GT`
 4. Add variant: `None`

 ##### Step 6: Capture The Spoiler Component

 For each variant:

 **Sport:**
 1. Select `Sport` variant
 2. Click **"+ Actor"** → select `BP_Car`
 3. In capture window, expand to find: `Spoiler → Static Mesh`
 4. **Check** the box
 5. Click OK
 6. In Captured Properties, set Static Mesh to: `SM_Spoiler_Sport`

 **GT:**
 1. Select `GT` variant
 2. Repeat above, set to: `SM_Spoiler_GT`

 **None:**
 1. Select `None` variant
 2. Repeat above, set to: `None` (empty)

 ##### Step 7: Test

 1. Click each variant in Variant Manager
 2. Spoiler should swap in the viewport
 3. Save everything

 ##### Step 8: Test Export

 The export will now include "Spoiler: Sport" (or whichever is active)!

 ---

 ### Removing Variant Sets

 Want to delete a variant set completely?

 #### Step-by-Step:

 1. Open Variant Set Editor (double-click `VariantSet` asset)
 2. **Right-click** the variant set you want to remove (e.g., "Tremolo")
 3. Click **"Delete Variant Set"**
 4. Confirm: **"Yes"**
 5. Save the asset (Ctrl + S)

 **That's it!** The export will automatically skip the deleted set.

 ---

 ### Editing Existing Variants

 #### Renaming A Variant:

 1. Open Variant Set Editor
 2. Expand the variant set (e.g., "Body Color")
 3. **Right-click** the variant (e.g., "Black")
 4. **"Rename"**
 5. Type new name: "Midnight Black"
 6. Press Enter
 7. Save

 #### Changing What A Variant Does:

 1. Select the variant
 2. Look at **Captured Properties** (bottom panel)
 3. Click on the property value (e.g., Material dropdown)
 4. Change to a different material
 5. Save

 #### Adding More Options To Existing Set:

 1. Select the variant set (e.g., "Body Color")
 2. Click **"+ Variant"**
 3. Name it (e.g., "Lime Green")
 4. Capture properties as shown earlier
 5. Set the green material
 6. Save

 ---

 ### Organizing Your Project

 As your project grows, stay organized!

 #### Folder Structure Best Practices:

 ```
 Content/
 ├── ProductAssets/
 │   ├── Meshes/
 │   │   ├── Car/
 │   │   │   ├── Body/
 │   │   │   ├── Wheels/
 │   │   │   └── Interior/
 │   │   └── Props/
 │   ├── Materials/
 │   │   ├── Car_BodyPaint/
 │   │   ├── Car_Chrome/
 │   │   └── Car_Glass/
 │   ├── Textures/
 │   ├── Blueprints/
 │   │   ├── BP_Car
 │   │   └── BP_CameraRig
 │   ├── Levels/
 │   │   └── Main
 │   └── VariantSet
 ```

 #### Naming Conventions:

 **Meshes:**
 - Static Mesh: `SM_CarBody`
 - Skeletal Mesh: `SK_Character`

 **Materials:**
 - Material: `M_CarPaint_Red`
 - Material Instance: `MI_CarPaint_Red`

 **Blueprints:**
 - Actor: `BP_Car`
 - Widget: `WBP_ExportButton`
 - Function Library: `BPL_Utilities`

 **Textures:**
 - Base Color: `T_Car_BC`
 - Normal: `T_Car_N`
 - Roughness: `T_Car_R`

 ---

 ## Part 4: Advanced Customization

 ---

 ### Changing Where PDFs Are Saved

 By default, PDFs save to: `F:\0personal\ProductConfigurator\Saved\PDFs\`

 Let's change it to: `F:\MyCarExports\PDFs\`

 #### Step 1: Install Visual Studio (If Not Already)

 1. Download Visual Studio 2022 Community
 2. During install, select "Game Development with C++"
 3. Install (takes 30min)

 #### Step 2: Open The Project In Visual Studio

 1. Close Unreal Engine
 2. Navigate to: `F:\0personal\ProductConfigurator\`
 3. **Right-click** `ProductConfigurator.uproject`
 4. **"Generate Visual Studio project files"**
 5. Wait (30 seconds)
 6. A new file appears: `ProductConfigurator.sln`
 7. **Double-click** `ProductConfigurator.sln`
 8. Visual Studio opens

 #### Step 3: Find The Export Code

 1. In Visual Studio, look at **Solution Explorer** (right panel)
 2. Expand: `ProductConfigurator → Source → ProductConfigurator → Private`
 3. **Double-click** `ConfigurationExportLibrary.cpp`
 4. File opens in editor

 #### Step 4: Change The PDF Directory

 1. Press **Ctrl + F** (Find)
 2. Search for: `Saved/PDFs`
 3. You'll find a line (around line 91):

 ```cpp
 FString PDFDir = FPaths::ProjectDir() / TEXT("Saved/PDFs");
 ```

 4. Change it to:

 ```cpp
 FString PDFDir = TEXT("F:/MyCarExports/PDFs");
 ```

 **Important Notes:**
 - Use **forward slashes** `/` not backslashes `\`
 - Keep `TEXT("...")` wrapper
 - Can use `FPaths::ProjectDir()` for relative paths

 #### Step 5: Also Change JSON Directory (Optional)

 Search for: `Saved/Configurations`

 Change line ~29:

 ```cpp
 FString SaveDir = TEXT("F:/MyCarExports/JSONFiles");
 ```

 #### Step 6: Save The File

 1. Press **Ctrl + S**
 2. File is saved

 #### Step 7: Build The Project

 1. In Visual Studio, top menu: **Build**
 2. Click **"Build Solution"** (or press Ctrl + Shift + B)
 3. Watch **Output** panel (bottom)
 4. Wait for: "Build succeeded"
 5. Takes 1-3 minutes

 #### Step 8: Launch Unreal From Visual Studio

 1. Make sure `ProductConfigurator` is set as startup project (bold in Solution Explorer)
 2. Press **F5** or click green **"Local Windows Debugger"** button
 3. Unreal Engine launches with your changes

 #### Step 9: Test

 1. Run an export (Python console test)
 2. Check: `F:\MyCarExports\PDFs\`
 3. Your PDF should be there!

 ---

 ### Changing File Names

 #### Current Format:
 ```
 Guitar_Configuration_2026-01-28_04-03-54.pdf
 ```

 #### Option 1: Remove Timestamp (Always Overwrite)

 **Edit** `ConfigurationExportLibrary.cpp`:

 Find (around line 31):

 ```cpp
 FString FileName = ConfigurationName.IsEmpty() 
     ? FString::Printf(TEXT("Config_%s.json"), *GetFormattedTimestamp())
     : FString::Printf(TEXT("%s_%s.json"), *ConfigurationName, *GetFormattedTimestamp());
 ```

 Change to:

 ```cpp
 FString FileName = ConfigurationName.IsEmpty() 
     ? TEXT("Configuration.json")
     : FString::Printf(TEXT("%s.json"), *ConfigurationName);
 ```

 **Result:**
 - Always creates `CarConfiguration.json` and `CarConfiguration.pdf`
 - Overwrites previous export

 #### Option 2: Add User Name To Filename

 ```cpp
 FString UserName = FPlatformProcess::UserName();
 FString FileName = FString::Printf(TEXT("%s_%s_%s.json"), 
     *ConfigurationName, 
     *UserName, 
     *GetFormattedTimestamp());
 ```

 **Result:**
 - `CarConfiguration_JohnDoe_2026-01-28_04-03-54.pdf`

 #### After Editing:

 1. Save file (Ctrl + S)
 2. Build Solution (Ctrl + Shift + B)
 3. Launch Unreal (F5)
 4. Test export

 ---

 ### Customizing The PDF Layout

 The PDF is generated by: `Scripts/generate_pdf.py`

 #### Step 1: Open The Script

 1. Navigate to: `F:\0personal\ProductConfigurator\Scripts\`
 2. **Right-click** `generate_pdf.py`
 3. **"Edit with"** → Choose **Notepad** or **VS Code**

 #### Step 2: Find The Layout Section

 Look for lines like:

 ```python
 lines.append('(Product Configuration Summary) Tj')
 lines.append('0 -25 Td /F1 11 Tf')
 lines.append('(Configuration: %s) Tj' % escape(config.get('configurationName', 'N/A')))
 ```

 #### Step 3: Change The Title

 Change:

 ```python
 lines.append('(Product Configuration Summary) Tj')
 ```

 To:

 ```python
 lines.append('(Car Configuration Report) Tj')
 ```

 #### Step 4: Add Your Company Name

 After the title line, add:

 ```python
 lines.append('0 -18 Td')
 lines.append('(My Company Name) Tj')
 ```

 #### Step 5: Save And Test

 1. Save the Python file
 2. Run an export from Unreal
 3. Check the PDF - it should have your changes!

 **No rebuild needed** - Python scripts run directly.

 ---

 ## Part 5: Troubleshooting & Help

 ---

 ### Common Problems & Solutions

 #### Problem 1: "Export Variant Sets To PDF node not found"

 **Cause:** Blueprint reflection hasn't updated.

 **Solution:**
 1. **Close** Unreal Engine completely (File → Exit)
 2. **Reopen** the project
 3. Open your Blueprint
 4. Search for the node again

 ---

 #### Problem 2: "No LevelVariantSets asset found"

 **Cause:** LevelVariantSetsActor is missing or not configured.

 **Solution:**
 1. Open your level
 2. Check **Outliner** for `LevelVariantSetsActor`
 3. If missing:
    - **Drag** `LevelVariantSetsActor` from "Place Actors" panel
    - In Details, assign your VariantSet asset
 4. If present:
    - Select it
    - Check "Level Variant Sets" property is assigned
    - If empty, click dropdown → select `/Game/ProductAssets/VariantSet`

 ---

 #### Problem 3: PDF not created

 **Cause 1:** Python not installed.

 **Solution:**
 1. Open Command Prompt (Windows key + R, type `cmd`)
 2. Type: `python --version`
 3. If error: Install Python from python.org
 4. **Important:** Check "Add Python to PATH" during install

 **Cause 2:** PDF script missing.

 **Solution:**
 1. Check: `F:\0personal\ProductConfigurator\Scripts\generate_pdf.py`
 2. If missing, the file got deleted - need to restore

 ---

 #### Problem 4: Wrong variants exported

 **Cause:** Different variant is active than you think.

 **Solution:**
 1. Open **Variant Manager** (Window → Cinematics → Variant Manager)
 2. Check which variant is highlighted (active) in each set
 3. Click the variant you want
 4. Try export again

 ---

 #### Problem 5: Can't build in Visual Studio

 **Error:** "MSB3073" or "C1083"

 **Solution:**
 1. Close Unreal Engine
 2. Delete these folders:
    - `Binaries`
    - `Intermediate`
    - `Saved` (warning: deletes your PDFs!)
 3. Right-click `.uproject` → "Generate Visual Studio project files"
 4. Open `.sln` in Visual Studio
 5. Build → Rebuild Solution

 ---

 #### Problem 6: Variant doesn't change anything

 **Cause:** No properties captured.

 **Solution:**
 1. Open Variant Set Editor
 2. Select the variant
 3. Check **Captured Properties** (bottom panel)
 4. If empty:
    - Click **"+ Actor"**
    - Select your car blueprint
    - Capture the properties you want to change
 5. Save

 ---

 ### Where To Get Help

 #### Official Resources:

 **Unreal Engine Documentation:**
 - https://docs.unrealengine.com/5.5/
 - Start here for official guides

 **Unreal Engine Forums:**
 - https://forums.unrealengine.com/
 - Ask questions, get help from community

 **Unreal Engine Discord:**
 - https://discord.gg/unreal-slackers
 - Real-time chat with other developers

 **YouTube Tutorials:**
 - Search: "Unreal Engine 5 Variant Manager tutorial"
 - Watch: Beginner Blueprint courses

 #### Specific Topics:

 **Learning Blueprints:**
 - Search: "Unreal Engine Blueprint for beginners"
 - Free course: Unreal Engine 5 Beginner Tutorial (YouTube)

 **Variant Manager Deep Dive:**
 - Epic Games: Variant Manager documentation
 - Search: "Unreal Variant Manager complete guide"

 **C++ Editing:**
 - Unreal C++ documentation
 - Book: "Unreal Engine 4 Game Development in 24 Hours"

 #### Getting Unstuck:

 **When asking for help, provide:**
 1. What you're trying to do
 2. What you expected to happen
 3. What actually happened
 4. Screenshots or error messages
 5. Your Unreal Engine version (5.5.4)

 ---

 ## Quick Reference Card


 ### File Locations Quick Guide

 | What | Where |
 |------|-------|
 | Project Root | `F:\0personal\ProductConfigurator\` |
 | 3D Assets | `Content/ProductAssets/Meshes/` |
 | Materials | `Content/ProductAssets/Materials/` |
 | Blueprints | `Content/ProductAssets/Blueprints/` |
 | Main Level | `Content/ProductAssets/Levels/Main` |
 | Variant Sets | `Content/ProductAssets/VariantSet` |
 | PDF Exports | `Saved/PDFs/` |
 | JSON Exports | `Saved/Configurations/` |
 | C++ Code | `Source/ProductConfigurator/` |
 | PDF Script | `Scripts/generate_pdf.py` |

 ### Variant Manager Workflow

 ```
 1. Open Variant Manager (Window → Cinematics → Variant Manager)
 2. Create Variant Set (+ Variant Set button)
 3. Add Variants (+ Variant button)
 4. Capture Properties (+ Actor → select object → check properties)
 5. Set Values (edit in Captured Properties panel)
 6. Test (click variants to see changes)
 7. Save (Ctrl + S)
 ```

 ### Export Test Code (Keep Handy!)

 ```python
 import unreal

 actors = unreal.get_editor_subsystem(unreal.EditorActorSubsystem).get_all_level_actors()
 variant_actor = None
 for actor in actors:
     if actor.get_class().get_name() == "LevelVariantSetsActor":
         variant_actor = actor
         break

 if variant_actor:
     result = unreal.ConfigurationExportLibrary.export_variant_sets_to_pdf(
         variant_actor,
         "TestExport"
     )
     success, pdf_path, error = result
     if success:
         print(f"✅ Success: {pdf_path}")
     else:
         print(f"❌ Error: {error}")
 ```

 ---


 ## Checklist: Your First Custom Configurator

 Use this checklist to build your first car configurator:

 - [ ] Install Unreal Engine 5.5.4
 - [ ] Install Visual Studio 2022
 - [ ] Install Python 3.x
 - [ ] Open ProductConfigurator project
 - [ ] Test PDF export with Python console
 - [ ] Import car 3D model
 - [ ] Create BP_Car blueprint
 - [ ] Add car components (body, wheels, etc.)
 - [ ] Place BP_Car in Main level
 - [ ] Delete old guitar actor
 - [ ] Open Variant Manager
 - [ ] Delete guitar variant sets
 - [ ] Create new "Body Color" variant set
 - [ ] Add variants: Red, Black, White
 - [ ] Capture car materials for each variant
 - [ ] Test variants in Variant Manager
 - [ ] Test PDF export with car
 - [ ] Verify PDF shows car variants
 - [ ] Save all assets
 - [ ] Backup project folder
 - [ ] Celebrate! 🎉

 ---

 **You're now ready to build amazing product configurators in Unreal Engine!**

 Good luck, and remember: every expert was once a beginner. You've got this! 💪

 ---

 **Last Updated:** January 30, 2026  
 **For:** Complete Beginners  
 **Unreal Engine Version:** 5.5.4
 
