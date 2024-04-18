(* open! Core *)
open! StdLabels
open! MoreLabels

let rec __ocaml_lex_refill_buf lexbuf _buf _len _curr _last =
  if lexbuf.Lexing.lex_eof_reached
  then 256, _buf, _len, _curr, _last
  else (
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    lexbuf.Lexing.refill_buff lexbuf;
    let _curr = lexbuf.Lexing.lex_curr_pos in
    let _last = lexbuf.Lexing.lex_last_pos in
    let _len = lexbuf.Lexing.lex_buffer_len in
    let _buf = lexbuf.Lexing.lex_buffer in
    if _curr < _len
    then Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
    else __ocaml_lex_refill_buf lexbuf _buf _len _curr _last)
;;

let rec __ocaml_lex_state4 lexbuf _last_action _buf _len _curr _last =
  let next_char, _buf, _len, _curr, _last =
    if _curr >= _len
    then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
    else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
  in
  match next_char with
  (* |'0' *)
  | 48 -> __ocaml_lex_state5 lexbuf _last_action _buf _len _curr _last
  | _ ->
    let _curr = _last in
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    _last_action

and __ocaml_lex_state5 lexbuf _last_action _buf _len _curr _last =
  let next_char, _buf, _len, _curr, _last =
    if _curr >= _len
    then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
    else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
  in
  match next_char with
  (* |'0' *)
  | 48 -> __ocaml_lex_state5 lexbuf _last_action _buf _len _curr _last
  (* |'1' *)
  | 49 ->
    let next_char, _buf, _len, _curr, _last =
      if _curr >= _len
      then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
      else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
    in
    (match next_char with
     (* |'1' *)
     | 49 -> __ocaml_lex_state10 lexbuf _last_action _buf _len _curr _last
     (* |'\n'|eof *)
     | 10 | 256 ->
       (* *)
       lexbuf.Lexing.lex_curr_pos <- _curr;
       lexbuf.Lexing.lex_last_pos <- _last;
       0
     (* |'\r' *)
     | 13 -> __ocaml_lex_state8 lexbuf _last_action _buf _len _curr _last
     (* |'0' *)
     | 48 -> __ocaml_lex_state9 lexbuf _last_action _buf _len _curr _last
     | _ ->
       let _curr = _last in
       lexbuf.Lexing.lex_curr_pos <- _curr;
       lexbuf.Lexing.lex_last_pos <- _last;
       _last_action)
  | _ ->
    let _curr = _last in
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    _last_action

and __ocaml_lex_state8 lexbuf _last_action _buf _len _curr _last =
  (* *)
  let _last = _curr in
  let _last_action = 0 in
  let next_char, _buf, _len, _curr, _last =
    if _curr >= _len
    then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
    else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
  in
  match next_char with
  (* |'\n' *)
  | 10 ->
    (* *)
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    0
  | _ ->
    let _curr = _last in
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    0 (* = last_action *)

and __ocaml_lex_state9 lexbuf _last_action _buf _len _curr _last =
  let next_char, _buf, _len, _curr, _last =
    if _curr >= _len
    then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
    else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
  in
  match next_char with
  (* |'1' *)
  | 49 -> __ocaml_lex_state12 lexbuf _last_action _buf _len _curr _last
  | _ ->
    let _curr = _last in
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    _last_action

and __ocaml_lex_state10 lexbuf _last_action _buf _len _curr _last =
  let next_char, _buf, _len, _curr, _last =
    if _curr >= _len
    then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
    else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
  in
  match next_char with
  (* |'1' *)
  | 49 -> __ocaml_lex_state10 lexbuf _last_action _buf _len _curr _last
  (* |'\n'|eof *)
  | 10 | 256 ->
    (* *)
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    0
  (* |'\r' *)
  | 13 -> __ocaml_lex_state8 lexbuf _last_action _buf _len _curr _last
  (* |'0' *)
  | 48 ->
    let next_char, _buf, _len, _curr, _last =
      if _curr >= _len
      then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
      else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
    in
    (match next_char with
     (* |'1' *)
     | 49 -> __ocaml_lex_state12 lexbuf _last_action _buf _len _curr _last
     (* |'0' *)
     | 48 -> __ocaml_lex_state5 lexbuf _last_action _buf _len _curr _last
     | _ ->
       let _curr = _last in
       lexbuf.Lexing.lex_curr_pos <- _curr;
       lexbuf.Lexing.lex_last_pos <- _last;
       _last_action)
  | _ ->
    let _curr = _last in
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    _last_action

and __ocaml_lex_state12 lexbuf _last_action _buf _len _curr _last =
  let next_char, _buf, _len, _curr, _last =
    if _curr >= _len
    then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
    else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
  in
  match next_char with
  (* |'\n'|eof *)
  | 10 | 256 ->
    (* *)
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    0
  (* |'\r' *)
  | 13 -> __ocaml_lex_state8 lexbuf _last_action _buf _len _curr _last
  (* |'0' *)
  | 48 -> __ocaml_lex_state9 lexbuf _last_action _buf _len _curr _last
  (* |'1' *)
  | 49 ->
    let next_char, _buf, _len, _curr, _last =
      if _curr >= _len
      then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
      else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
    in
    (match next_char with
     (* |'0' *)
     | 48 -> __ocaml_lex_state4 lexbuf _last_action _buf _len _curr _last
     | _ ->
       let _curr = _last in
       lexbuf.Lexing.lex_curr_pos <- _curr;
       lexbuf.Lexing.lex_last_pos <- _last;
       _last_action)
  | _ ->
    let _curr = _last in
    lexbuf.Lexing.lex_curr_pos <- _curr;
    lexbuf.Lexing.lex_last_pos <- _last;
    _last_action
;;

let read lexbuf =
  let __ocaml_lex_result =
    let _curr = lexbuf.Lexing.lex_curr_pos in
    let _last = _curr in
    let _len = lexbuf.Lexing.lex_buffer_len in
    let _buf = lexbuf.Lexing.lex_buffer in
    let _last_action = -1 in
    lexbuf.Lexing.lex_start_pos <- _curr;
    let next_char, _buf, _len, _curr, _last =
      if _curr >= _len
      then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
      else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
    in
    match next_char with
    (* |'0' *)
    | 48 ->
      (* *)
      let _last = _curr in
      let _last_action = 1 in
      let next_char, _buf, _len, _curr, _last =
        if _curr >= _len
        then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
        else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
      in
      (match next_char with
       (* |'1' *)
       | 49 -> __ocaml_lex_state12 lexbuf 1 (* = last_action *) _buf _len _curr _last
       | _ ->
         let _curr = _last in
         lexbuf.Lexing.lex_curr_pos <- _curr;
         lexbuf.Lexing.lex_last_pos <- _last;
         1 (* = last_action *))
    (* |eof *)
    | 256 ->
      let _curr = _last in
      lexbuf.Lexing.lex_curr_pos <- _curr;
      lexbuf.Lexing.lex_last_pos <- _last;
      _last_action
    (* |'1' *)
    | 49 ->
      (* *)
      let _last = _curr in
      let _last_action = 1 in
      let next_char, _buf, _len, _curr, _last =
        if _curr >= _len
        then __ocaml_lex_refill_buf lexbuf _buf _len _curr _last
        else Char.code (Bytes.unsafe_get _buf _curr), _buf, _len, _curr + 1, _last
      in
      (match next_char with
       (* |'0' *)
       | 48 -> __ocaml_lex_state4 lexbuf 1 (* = last_action *) _buf _len _curr _last
       | _ ->
         let _curr = _last in
         lexbuf.Lexing.lex_curr_pos <- _curr;
         lexbuf.Lexing.lex_last_pos <- _last;
         1 (* = last_action *))
    | _ ->
      (* *)
      lexbuf.Lexing.lex_curr_pos <- _curr;
      lexbuf.Lexing.lex_last_pos <- _last;
      1
  in
  (let _curr_p = lexbuf.Lexing.lex_curr_p in
   if _curr_p != Lexing.dummy_pos
   then (
     lexbuf.Lexing.lex_start_p <- _curr_p;
     lexbuf.Lexing.lex_curr_p
     <- { _curr_p with
          Lexing.pos_cnum = lexbuf.Lexing.lex_abs_pos + lexbuf.Lexing.lex_curr_pos
        }));
  match __ocaml_lex_result with
  | 0 -> print_endline "SUBMARINE"
  | 1 -> print_endline "NOISE"
  | _ -> raise (Failure "lexing: empty token")
;;

let () =
  let lexbuf = Lexing.from_channel stdin in
  read lexbuf
;;
