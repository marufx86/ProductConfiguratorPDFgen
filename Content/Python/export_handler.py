import unreal
    import json
    import os
    from datetime import datetime

    def export_config_to_json_and_pdf():
        """Export configuration to JSON"""
        try:
            world = unreal.get_editor_subsystem(unreal.UnrealEditorSubsystem).get_editor_world()
            configurator_class = unreal.load_class(None, "/Game/ProductConfig/Blueprints/BP_Configurator.BP_Configurator_C")
            actors = unreal.GameplayStatics.get_all_actors_of_class(world, configurator_class)
            
            if not actors:
                return "ERROR: No BP_Configurator in level"
            
            config_actor = actors[0]
            obj_variants = config_actor.get_editor_property("ObjectVariantSets")
            env_var = config_actor.get_editor_property("EnviroVarSet")
            cam_var = config_actor.get_editor_property("CameraVarSet")
            
            timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
            config = {
                "ConfigurationName": "ProductConfiguration",
                "Timestamp": timestamp,
                "SelectedVariants": [],
                "SelectedEnvironment": "",
                "SelectedCamera": ""
            }
            
            if obj_variants:
                for var_struct in obj_variants:
                    vs = var_struct.get_editor_property("VariantSet_5_53DD780140AA80DE303F9FB135D2EA55")
                    idx = var_struct.get_editor_property("currentIndex_2_CE1166BB489772853E83B4987669778D")
                    if vs and idx >= 0:
                        variant = vs.get_variant(idx)
                        if variant:
                            config["SelectedVariants"].append(str(variant.get_display_text()))
            
            if env_var:
                vs = env_var.get_editor_property("VariantSet_5_53DD780140AA80DE303F9FB135D2EA55")
                idx = env_var.get_editor_property("currentIndex_2_CE1166BB489772853E83B4987669778D")
                if vs and idx >= 0:
                    variant = vs.get_variant(idx)
                    if variant:
                        config["SelectedEnvironment"] = str(variant.get_display_text())
            
            if cam_var:
                vs = cam_var.get_editor_property("VariantSet_5_53DD780140AA80DE303F9FB135D2EA55")
                idx = cam_var.get_editor_property("currentIndex_2_CE1166BB489772853E83B4987669778D")
                if vs and idx >= 0:
                    variant = vs.get_variant(idx)
                    if variant:
                        config["SelectedCamera"] = str(variant.get_display_text())
            
            project_dir = unreal.Paths.project_dir()
            saved_dir = unreal.Paths.project_saved_dir()
            config_dir = os.path.join(saved_dir, "Configurations")
            os.makedirs(config_dir, exist_ok=True)
            
            json_file = f"Config_{timestamp}.json"
            json_path = os.path.join(config_dir, json_file)
            
            with open(json_path, "w", encoding="utf-8") as f:
                json.dump(config, f, indent=2)
            
            return f"SUCCESS! JSON exported: {json_file}"
        except Exception as e:
            import traceback
            traceback.print_exc()
            return f"Failed: {str(e)}"
    