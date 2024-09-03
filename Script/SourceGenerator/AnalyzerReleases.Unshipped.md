### Dynamic Rules

| Rule ID    | Category     | Severity | Notes                                                                                                                                                                 |
|------------|--------------|----------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| UC_ERROR01 | UnrealCSharp | Error    | The partial keyword must be added to the dynamic class/dynamic struct to ensure that the source generator adds the necessary code to the dynamic class/dynamic struct |
| UC_ERROR02 | UnrealCSharp | Error    | Dynamic classes inherited from blueprints must end with "_C", dynamic AActor classes inherited from C++ must start with "A" or end with "_C", dynamic non Actor classes inherited from C++ must start with "U" or end with "_C", and dynamic structures must start with "F" |
| UC_ERROR03 | UnrealCSharp | Error    | The file name where the dynamic class and dynamic struct are located must be consistent with the class name (excluding A, U, or F) |
| UC_ERROR04 | UnrealCSharp | Error    | The namespace of dynamic class/struct/interface/enum must be "Script.CoreUObject" |
