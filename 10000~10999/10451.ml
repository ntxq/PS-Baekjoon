let countCycles adj =
  let visited = Array.init (Array.length adj) (fun _ -> false) in
  let rec dfs u =
    visited.(u) <- true;
    if not visited.(adj.(u)) then dfs adj.(u)
  in
  let rec loop idx count =
    if idx = Array.length adj then count
    else if visited.(idx) then loop (idx + 1) count
    else (
      dfs idx;
      loop (idx + 1) (count + 1))
  in
  loop 0 0

let () =
  for _ = 1 to read_int () do
    let _ = read_int () in
    read_line () |> String.split_on_char ' ' |> List.map int_of_string
    |> List.map (fun x -> x - 1)
    |> Array.of_list |> countCycles |> string_of_int |> print_endline
  done