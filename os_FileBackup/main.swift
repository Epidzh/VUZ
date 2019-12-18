import Foundation


struct File {
    let path: String
    var attributes: [FileAttributeKey: Any]
}


extension Array where Element == File {
    mutating func getFilesFromDir(path: String) {
        if let tmp = URL(string: path) {
            do {
                for i in try FileManager.default.contentsOfDirectory(at: tmp, includingPropertiesForKeys: nil) {
                    var isDirectory: ObjCBool = false
                    let exists = FileManager.default.fileExists(atPath: i.path, isDirectory: &isDirectory)

                    switch (exists, isDirectory.boolValue) {
                        case (true, false): self.append(File(path: i.path, attributes: try FileManager.default.attributesOfItem(atPath: i.path)))
                        case (true, true): getFilesFromDir(path: i.path)
                        default: ()
                    }
                }
            } catch {
                print("Some error!")
            }
        }
        else {
            print("Incorrect dir!")
        }
    }
}


var backupFiles: [File] = []
let sourceFolder = FileManager.default.currentDirectoryPath
if CommandLine.arguments.count == 1 {
    backupFiles.getFilesFromDir(path: FileManager.default.currentDirectoryPath)
}
else {
    for i in 1..<CommandLine.arguments.count {
        do {
            let path = FileManager.default.currentDirectoryPath + "/" + CommandLine.arguments[i]
            let info = try FileManager.default.attributesOfItem(atPath: path)
            backupFiles.append(File(path: path, attributes: info))
        } catch {
            print("\(CommandLine.arguments[i]): This is not a file")
        }    
    }
}


for i in backupFiles {
    print(i.path)
}


