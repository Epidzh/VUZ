import Foundation

var tmp = FileManager.default.currentDirectoryPath
do {
    for i in try FileManager.default.contentsOfDirectory(at: URL(string: tmp)!, includingPropertiesForKeys: nil) {
        var isDirectory: ObjCBool = false
        let exists = FileManager.default.fileExists(atPath: i.path, isDirectory: &isDirectory)

        switch (exists, isDirectory.boolValue) {
            case (true, false): print("\(i.path) -> file!")
            case (true, true): print("\(i.path) -> dir!")
            default: ()
        }
    }
} catch {
    print("Some error!")
}