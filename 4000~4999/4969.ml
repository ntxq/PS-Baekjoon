open! Core

let prime_numbers =
  let sieve = Array.create ~len:300001 true in
  sieve.(0) <- false;
  sieve.(1) <- false;
  for i = 2 to 300000 do
    if not (i % 7 = 1 || i % 7 = 6) then sieve.(i) <- false;
    if sieve.(i)
    then (
      let rec loop j =
        if j <= 300000
        then (
          sieve.(j) <- false;
          loop (j + i))
      in
      loop (i * 2))
  done;
  Array.foldi sieve ~init:[] ~f:(fun i acc x -> if x then i :: acc else acc) |> List.rev
;;

let () =
  In_channel.input_lines In_channel.stdin
  |> List.map ~f:Int.of_string
  |> List.drop_last_exn
  |> List.iter ~f:(fun n ->
    let factors =
      List.filter prime_numbers ~f:(fun x -> n % x = 0)
      |> List.map ~f:Int.to_string
      |> String.concat ~sep:" "
    in
    Out_channel.output_string stdout [%string "%{n#Int}: %{factors}\n"])
;;
