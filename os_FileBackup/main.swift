import Foundation


struct File {
    let path: String
    var attributes: [FileAttributeKey: Any]
}


func getCurrentDate() -> String {
    let date = Date()
    let calendar = Calendar.current
    let day = calendar.component(.day, from: date)
    let month = calendar.component(.month, from: date)
    let year = calendar.component(.year, from: date)
    let hour = calendar.component(.hour, from: date)
    let minutes = calendar.component(.minute, from: date)
    let seconds = calendar.component(.second, from: date)
    return "\(day).\(month).\(year)*\(hour):\(minutes):\(seconds)"
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
let destFolder = "/Users/seryogas/Desktop"
let rotationTime = 604800
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
            print("\(CommandLine.arguments[i]): This is not file or dir!")
        }    
    }
}


for i in backupFiles {
    print(i.path)
}


if backupFiles.count > 0 {

    let currBackupFolderPathURL = URL(string: destFolder)!.appendingPathComponent("/MY_BACKUPS" + "/" + (sourceFolder + getCurrentDate()).replacingOccurrences(of: "/", with: "->", options: .literal, range: nil))
    if !FileManager.default.fileExists(atPath: currBackupFolderPathURL.path) {
    do {
        try FileManager.default.createDirectory(atPath: currBackupFolderPathURL.path, withIntermediateDirectories: true, attributes: nil)
    } catch {
        print("Create directory failed \(error.localizedDescription)");
    }
}
    for i in backupFiles {
        do {
            print(i.path)
            try FileManager.default.copyItem(atPath: i.path, toPath: currBackupFolderPathURL.path + "/" + FileManager.default.displayName(atPath: i.path))
        } catch let error{
            print("Copy file failed: \(error.localizedDescription)")
        }
    }
}
else {
    print("Nothing to backup!")
}